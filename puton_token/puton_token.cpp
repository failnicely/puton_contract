#include "./puton_token.hpp"

const uint64_t SCEHDULE_INTERVAL = 10; // sec

void puton_token::readdb()
{
    require_auth(_self);

    user_table users(N(puton), N(puton));
    post_table posts(N(puton), N(puton));

    for (auto &u : users)
    {
        eosio::print("user: ", name{u.account}, "\n");
    }

    for (auto &p : posts)
    {
        eosio::print("post: ", p.ipfs_addr, "\n");
    }
}

void puton_token::startserver()
{
    require_auth(_self);

    // read data from puton db
    // cannot modify objects in table of another contract
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
    tx.delay_sec = SCEHDULE_INTERVAL; 
    tx.send(_self + now(), _self); // needs a unique sender id so append current time
}