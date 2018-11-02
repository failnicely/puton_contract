#include "../table/struct.cpp"
#include <eosiolib/transaction.hpp>

using namespace eosio;
using std::string;

class puton_token : eosio::contract
{

  public:
    puton_token(account_name _self) : contract::contract(_self) {}

    // @abi action
    void reward();

  private:
    // define tables for puton_service
    typedef multi_index<N(users), user> puton_users;
    typedef multi_index<N(posts), post> puton_posts;
};

EOSIO_ABI(puton_token, (reward))