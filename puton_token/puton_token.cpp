#include "./puton_token.hpp"

const uint64_t THREE_SEC = 5; 

void puton_token::readdb()
{
    require_auth(_self);

    user_table users(N(puton), N(puton));
    post_table posts(N(puton), N(puton));

    for (auto &row : users)
    {
        eosio::print("user: ", name{row.account}, "\n");
    }

    for (auto &row : posts)
    {
        eosio::print("post: ", row.ipfs_addr.c_str(), "\n");
    }
}

void puton_token::startserver(account_name puton, bool is_first)
{
    require_auth(puton);

    if (is_first) {
        eosio::print("start puton_token scheduling");
    }

    // read data from puton db
    post_table posts(N(puton), N(puton));
    for (auto &p: posts)
    {
        eosio::print("post#", p.id, ", author: ", name{p.author}, ", ipfs: ", p.ipfs_addr, "\n");
    }

    // deferred transaction to do again
    eosio::transaction tx;
    tx.actions.emplace_back(
        permission_level{_self, N(active)},
        _self, N(startserver),
        std::make_tuple(_self, false));
    tx.delay_sec = THREE_SEC; 
    tx.send(_self + now(), _self); // needs a unique sender id so append current time
}