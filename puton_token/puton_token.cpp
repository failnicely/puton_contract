#include<puton_token.hpp>

void puton_token::read()
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
