#!/bin/bash

cleos wallet open
cleos wallet open -n tak

cleos wallet unlock --password PW5KRyUSVq3Ytht2mwHNx5ZQWYWginSJkiEhU5n6LWL6ehattytK2
cleos wallet unlock -n tak --password PW5KBvksXaoDgkQcCCnkFLbfxMUW5e5TK3hYZi5MhsW5duzzexdnV

cleos create account eosio puton EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
cleos create account eosio puton.token EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
cleos create account eosio tak EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
cleos create account eosio curl EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

cleos set account permission puton active '{"threshold": 1,"keys": [{"key": "EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8","weight": 1}],"accounts": [{"permission":{"actor":"puton","permission":"eosio.code"},"weight":1}]}' owner -p puton


cd puton
./build.sh puton puton

cleos push action puton createuser '["tak"]' -p tak
sleep 0.6
cleos push action puton createuser '["curl"]' -p curl
sleep 0.6

cleos push action puton addpost '["tak", "TAK_IPFS_ADDR_1"]' -p tak
sleep 0.6
cleos push action puton addpost '["tak", "TAK_IPFS_ADDR_2"]' -p tak
sleep 0.6
cleos push action puton addpost '["curl", "CURL_IPFS_ADDR_1"]' -p curl
sleep 0.6
cleos push action puton addpost '["curl", "CURL_IPFS_ADDR_2"]' -p curl
sleep 0.6

cleos push action puton likepost '["tak", "2"]' -p tak
sleep 0.6
cleos push action puton likepost '["curl", "1"]' -p curl
sleep 0.6
cleos push action puton likepost '["curl", "2"]' -p curl

cleos push action puton addcmt '["curl", "0", "comment"]' -p curl
sleep 0.6
cleos push action puton addcmt '["tak", "1", "comment"]' -p tak
sleep 0.6

cd ../puton_token
./build.sh puton.token puton_token

# cleos push action puton.token readdb '[""]' -p puton.token
# start server
cleos push action puton.token startserver '[""]' -p puton.token

