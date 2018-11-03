#include "../table/struct.cpp"
#include <eosiolib/transaction.hpp>
#include <eosiolib/asset.hpp>

using namespace eosio;
using std::string;

class puton_token : public contract
{

public:
  puton_token(account_name _self) : contract(_self) {}

  /// for puton_service

  // @abi action
  void reward();

  /// for contract

  // @abi action
  void create(account_name issuer, asset maximum_supply);

  // @abi action
  void issue(account_name to, asset quantity, string memo);

  // @abi action
  void transfer(account_name from, account_name to, asset quantity, string memo);

  inline asset get_supply(symbol_name sym) const;

  inline asset get_balance(account_name owner, symbol_name sym) const;

  // @abi table
  struct transfer_args
  {
    account_name from;
    account_name to;
    asset quantity;
    string memo;
  };

private:
  /// for token contract

  struct account
  {
    asset balance;

    uint64_t primary_key() const { return balance.symbol.name(); }

    EOSLIB_SERIALIZE(account, (balance))
  };

  struct currency_stats
  {
    asset supply;
    asset max_supply;
    account_name issuer;

    uint64_t primary_key() const { return supply.symbol.name(); }

    EOSLIB_SERIALIZE(currency_stats, (supply)(max_supply)(issuer))
  };

  // @abi table
  typedef multi_index<N(accounts), account> accounts;
  // @abi table
  typedef multi_index<N(stat), currency_stats> stats;

  void sub_balance(account_name owner, asset value);
  void add_balance(account_name owner, asset value, account_name ram_payer);

  /// for puton_service

  // define tables for puton_service
  typedef multi_index<N(users), user> puton_users;
  typedef multi_index<N(posts), post> puton_posts;
};

asset puton_token::get_supply(symbol_name sym) const
{
    stats statstable(_self, sym);
    const auto &st = statstable.get(sym);
    return st.supply;
}

asset puton_token::get_balance(account_name owner, symbol_name sym) const
{
    accounts accountstable(_self, owner);
    const auto &ac = accountstable.get(sym);
    return ac.balance;
}

EOSIO_ABI(puton_token, (reward)(create)(issue)(transfer))