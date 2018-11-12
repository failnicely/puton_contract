#!/bin/bash


cleos push action puton addpost '["tak", "TAK_IPFS_ADDR_1"]' -p tak
sleep 0.6

cleos push action puton addcmt '["curl", "0", "comment"]' -p curl
sleep 0.6
cleos push action puton addcmt '["camry", "0", "comment"]' -p camry
sleep 0.6
cleos push action puton addcmt '["tak", "0", "comment"]' -p tak
sleep 0.6

cleos push action puton likepost '["curl", "0"]' -p curl
sleep 0.6

cleos push action puton likepost '["camry", "0"]' -p camry
sleep 0.6

while [ : ]
do

cleos push action puton addpost '["tak", "TAK_IPFS_ADDR_1"]' -p tak
sleep 10
cleos push action puton addpost '["tak", "TAK_IPFS_ADDR_2"]' -p tak
sleep 10
cleos push action puton addpost '["curl", "CURL_IPFS_ADDR_1"]' -p curl
sleep 10
cleos push action puton addpost '["curl", "CURL_IPFS_ADDR_2"]' -p curl
sleep 10
cleos push action puton addpost '["curl", "CURL_IPFS_ADDR_3"]' -p curl
sleep 10

cleos push action puton addcmt '["curl", "0", "comment"]' -p curl
sleep 0.6
cleos push action puton addcmt '["tak", "1", "comment"]' -p tak
sleep 0.6

done