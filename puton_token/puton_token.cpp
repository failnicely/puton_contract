#include "./puton_token.hpp"

const unsigned_int SCEHDULE_INTERVAL = 10; // sec

void puton_token::reward()
{
    require_auth(_self);

    // read data from puton_service db
    // cannot modify objects in table of another contract
    puton_posts posts(N(puton), N(puton));
    for (auto &p : posts)
    {
        eosio::print("post#", p.id, ", author: ", name{p.author}, ", ipfs: ", p.ipfs_addr, "\n");
    }

    // deferred transaction to do again
    eosio::transaction tx;
    tx.actions.emplace_back(
        permission_level{_self, N(active)},
        _self, N(reward),
        std::make_tuple());
    tx.delay_sec = SCEHDULE_INTERVAL;
    tx.send(_self + now(), _self); // needs a unique sender id so append current time
}