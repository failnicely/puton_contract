#!/bin/bash

cleos create account eosio taktak EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
cleos create account eosio curlcurl EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
cleos create account eosio camrycamry EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
cleos create account eosio jinnyjinny EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
cleos create account eosio uniuni EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
# create puton user
cleos push action puton createuser '["taktak"]' -p taktak
sleep 0.6
cleos push action puton createuser '["curlcurl"]' -p curlcurl
sleep 0.6
cleos push action puton createuser '["jinnyjinny"]' -p jinnyjinny
sleep 0.6
cleos push action puton createuser '["camrycamry"]' -p camrycamry
sleep 0.6
cleos push action puton createuser '["uniuni"]' -p uniuni
sleep 0.6


i="0"
puton_user=("tak" "curl" "camry" "jinny" "uni","taktak" "curlcurl" "jinnyjinny" "camrycamry" "uniuni")

while [ : ]
do

# set random user
rand=$[$RANDOM % ${#puton_user[@]}]
user=${puton_user[$rand]}

# create post
cleos push action puton addpost '['$user', "IPFS_ADDR_'$i'"]' -p $user
sleep 3
# add comment
cleos push action puton addcmt '["curl", '$i', "comment_curl"]' -p curl
sleep 3
cleos push action puton addcmt '["camry", '$i', "comment_camry"]' -p camry
sleep 3
cleos push action puton addcmt '["jinny", '$i', "comment_jinny"]' -p jinny
sleep 3
cleos push action puton addcmt '["uni", '$i', "comment_uni"]' -p uni
sleep 3
cleos push action puton addcmt '["tak", '$i', "comment_tak"]' -p tak
sleep 3
# like post
cleos push action puton likepost '["curl", '$i']' -p curl
sleep 3
cleos push action puton likepost '["camry", '$i']' -p camry
sleep 3
cleos push action puton likepost '["jinny", '$i']' -p jinny
sleep 3
cleos push action puton likepost '["uni", '$i']' -p uni
sleep 3
cleos push action puton likepost '["tak", '$i']' -p tak
sleep 3

sleep 15

i=$[$i+1]
done