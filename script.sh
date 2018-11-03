#!/bin/bash

# open wallet
cleos wallet open
cleos wallet open -n tak

# unlock wallet
cleos wallet unlock --password PW5KRyUSVq3Ytht2mwHNx5ZQWYWginSJkiEhU5n6LWL6ehattytK2
cleos wallet unlock -n tak --password PW5KBvksXaoDgkQcCCnkFLbfxMUW5e5TK3hYZi5MhsW5duzzexdnV

# create eos account for test
cleos create account eosio puton EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
cleos create account eosio puton.token EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
cleos create account eosio tak EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
cleos create account eosio curl EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

# build & set puton
cd puton
./build.sh puton puton

# create puton user
cleos push action puton createuser '["tak"]' -p tak
sleep 0.6
cleos push action puton createuser '["curl"]' -p curl
sleep 0.6

# add post to puton_service
cleos push action puton addpost '["tak", "TAK_IPFS_ADDR_1"]' -p tak
sleep 0.6
cleos push action puton addpost '["tak", "TAK_IPFS_ADDR_2"]' -p tak
sleep 0.6
cleos push action puton addpost '["curl", "CURL_IPFS_ADDR_1"]' -p curl
sleep 0.6
cleos push action puton addpost '["curl", "CURL_IPFS_ADDR_2"]' -p curl
sleep 0.6

# like post 
cleos push action puton likepost '["tak", "2"]' -p tak
sleep 0.6
cleos push action puton likepost '["curl", "1"]' -p curl
sleep 0.6
cleos push action puton likepost '["curl", "2"]' -p curl

# add comment to post
cleos push action puton addcmt '["curl", "0", "comment"]' -p curl
sleep 0.6
cleos push action puton addcmt '["tak", "1", "comment"]' -p tak
sleep 0.6

# build & set puton_token
cd ../puton_token
./build.sh puton.token puton_token

# start reward
cleos push action puton.token reward '[""]' -p puton.token

