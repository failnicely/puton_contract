#include "../table/struct.cpp"
#include <eosiolib/symbol.hpp>
#include <eosiolib/asset.hpp>

using namespace eosio;
using std::string;

class puton_token : public contract
{

public:
  puton_token(account_name _self) : contract(_self) {}

  /// for token contract

  // @abi action
  void create(account_name issuer, asset maximum_supply);

  // @abi action
  void issue(account_name to, asset quantity, string memo);

  // @abi action
  void transfer(account_name from, account_name to, asset quantity, string memo);

  inline asset get_supply(symbol_name sym) const;
  inline asset get_balance(account_name owner, symbol_name sym) const;

  struct transfer_args
  {
    account_name from;
    account_name to;
    asset quantity;
    string memo;
  };

  /// for puton_service

  // @abi action
  void reward(uint16_t week);

private:
  /// for token contract

  //@abi table accounts i64
  struct account
  {
    asset balance;

    uint64_t primary_key() const { return balance.symbol.name(); }
  };

  //@abi table stat i64
  struct currency
  {
    asset supply;
    asset max_supply;
    account_name issuer;
    uint64_t last_total_point;

    uint64_t primary_key() const { return supply.symbol.name(); }
  };

  typedef multi_index<N(accounts), account> accounts;
  typedef multi_index<N(stat), currency> stats;

  void sub_balance(account_name owner, asset value);
  void add_balance(account_name owner, asset value, account_name ram_payer);

  // private var
  symbol_type PTN_SYMBOL = symbol_type(string_to_symbol(3, "PTN"));

  /// for puton_service

  // define tables for puton_service
  typedef multi_index<N(users), user> puton_users;
  typedef multi_index<N(posts), post, 
    indexed_by<N(created_at), const_mem_fun<post, uint64_t, &post::by_created_at>>,
    indexed_by<N(author), const_mem_fun<post, account_name, &post::by_author>>
  > puton_posts;

  // private func
  void set_total_point(uint64_t);
  uint64_t get_last_total_point();
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