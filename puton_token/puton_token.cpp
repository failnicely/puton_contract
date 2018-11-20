#include "./puton_token.hpp"

// const uint64_t REWARD_INTERVAL = 7 * 86400; // 7 days
// const uint64_t THREE_DAYS = 3 * 86400; // 3 days
// const uint64_t TEN_DAYS = 10 * 86400; // 10 days

const uint64_t REWARD_INTERVAL = 7 * 60;
const uint64_t THREE_DAYS = 3 * 60;
const uint64_t TEN_DAYS = 10 * 60;

// TODO: add tmp struct
struct rewardrow
{
    account_name author = 0;
    uint16_t total_point = 0;
};

void puton_token::reward(bool is_first)
{
    require_auth(_self);
    if (is_first)
    {
        eosio::print("puton.token rewarding started");
    }

    if (!is_first)
    {
        // read data from puton_service db
        // cannot modify objects in table of another contract
        puton_posts posts(N(puton), N(puton));
        auto post_index = posts.get_index<N(created_at)>();
        auto begin = post_index.lower_bound(now() - TEN_DAYS);
        auto end = post_index.lower_bound(now() - THREE_DAYS);

        // issue token to puton.token
        uint64_t total_point = 0;
        std::vector<rewardrow> reward_rows;

        std::for_each(begin, end, [&](auto &p) {
            // calc total_point
            total_point += p.point;
        });

        // transfer PTN to author
        eosio::print("is_first: ", is_first, ", range: ", now() - TEN_DAYS, " ~ ", now() - THREE_DAYS, "\n");
        eosio::print("----------------------------------------------------------\n");
        std::for_each(begin, end, [&](auto &p) {
            eosio::print("post#", p.id, ", author: ", name{p.author}, ", created_at: ", p.created_at, ", point: ");
            printi(p.point);
            eosio::print("\n");

            // transfer PTN token to author
            const bool is_positive_point = (p.point > 0);
            if (is_positive_point)
            {
                eosio::print("send inline action to issue PTN token\n");
                asset quantity = eosio::asset(p.point * 1000 / total_point, PTN_SYMBOL);
                SEND_INLINE_ACTION(*this, issue, {_self, N(active)}, {p.author, quantity, "rewarded post"});
                // SEND_INLINE_ACTION(*this, transfer, {_self, N(active)}, {_self, p.author, quantity, "rewarded post"});
            }
        });
    }

    // deferred transaction to do again
    eosio::transaction tx;
    tx.actions.emplace_back(
        permission_level{_self, N(active)},
        _self, N(reward),
        std::make_tuple(false)); // is_first: false
    // 처음 서비스 시작할 때 reward 액션 날린다고 가정함
    // 첫 번째(서비스 시작할 때) 10일 후에 실행 -> 이 후에는 7일마다
    tx.delay_sec = is_first ? TEN_DAYS : REWARD_INTERVAL;
    tx.send(_self + now(), _self); // needs a unique sender id so append current time
}

void puton_token::create(account_name issuer, asset maximum_supply)
{
    require_auth(_self);

    auto sym = maximum_supply.symbol;
    eosio_assert(sym.is_valid(), "invalid symbol name");
    eosio_assert(maximum_supply.is_valid(), "invalid supply");
    eosio_assert(maximum_supply.amount > 0, "max-supply must be positive");

    stats statstable(_self, sym.name());
    auto existing = statstable.find(sym.name());
    eosio_assert(existing == statstable.end(), "token with symbol already exists");

    statstable.emplace(_self, [&](auto &s) {
        s.supply.symbol = maximum_supply.symbol;
        s.max_supply = maximum_supply;
        s.issuer = issuer;
    });
}

void puton_token::issue(account_name to, asset quantity, string memo)
{
    auto sym = quantity.symbol;
    eosio_assert(sym.is_valid(), "invalid symbol name");
    eosio_assert(memo.size() <= 256, "memo has more than 256 bytes");

    auto sym_name = sym.name();
    stats statstable(_self, sym_name);
    auto existing = statstable.find(sym_name);
    eosio_assert(existing != statstable.end(), "token with symbol does not exist, create token before issue");
    const auto &st = *existing;

    require_auth(st.issuer);
    eosio_assert(quantity.is_valid(), "invalid quantity");
    eosio_assert(quantity.amount > 0, "must issue positive quantity");

    eosio_assert(quantity.symbol == st.supply.symbol, "symbol precision mismatch");
    eosio_assert(quantity.amount <= st.max_supply.amount - st.supply.amount, "quantity exceeds available supply");

    statstable.modify(st, 0, [&](auto &s) {
        s.supply += quantity;
    });

    add_balance(st.issuer, quantity, st.issuer);

    if (to != st.issuer)
    {
        SEND_INLINE_ACTION(*this, transfer, {st.issuer, N(active)}, {st.issuer, to, quantity, memo});
    }
}

void puton_token::transfer(account_name from, account_name to, asset quantity, string memo)
{
    eosio_assert(from != to, "cannot transfer to self");
    require_auth(from);
    eosio_assert(is_account(to), "to account does not exist");
    auto sym = quantity.symbol.name();
    stats statstable(_self, sym);
    const auto &st = statstable.get(sym);

    require_recipient(from);
    require_recipient(to);

    eosio_assert(quantity.is_valid(), "invalid quantity");
    eosio_assert(quantity.amount > 0, "must transfer positive quantity");
    eosio_assert(quantity.symbol == st.supply.symbol, "symbol precision mismatch");
    eosio_assert(memo.size() <= 256, "memo has more than 256 bytes");

    sub_balance(from, quantity);
    add_balance(to, quantity, from);
}

void puton_token::sub_balance(account_name owner, asset value)
{
    accounts from_acnts(_self, owner);

    const auto &from = from_acnts.get(value.symbol.name(), "no balance object found");
    eosio_assert(from.balance.amount >= value.amount, "overdrawn balance");

    if (from.balance.amount == value.amount)
    {
        from_acnts.erase(from);
    }
    else
    {
        from_acnts.modify(from, owner, [&](auto &a) {
            a.balance -= value;
        });
    }
}

void puton_token::add_balance(account_name owner, asset value, account_name ram_payer)
{
    accounts to_acnts(_self, owner);
    auto to = to_acnts.find(value.symbol.name());
    if (to == to_acnts.end())
    {
        to_acnts.emplace(ram_payer, [&](auto &a) {
            a.balance = value;
        });
    }
    else
    {
        to_acnts.modify(to, 0, [&](auto &a) {
            a.balance += value;
        });
    }
}