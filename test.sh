#!/bin/bash

while [ : ]
do

cleos push action puton addpost '["tak", "TAK_IPFS_ADDR_1"]' -p tak
sleep 0.6
cleos push action puton addpost '["tak", "TAK_IPFS_ADDR_2"]' -p tak
sleep 0.6
cleos push action puton addpost '["curl", "CURL_IPFS_ADDR_1"]' -p curl
sleep 0.6
cleos push action puton addpost '["curl", "CURL_IPFS_ADDR_2"]' -p curl
sleep 0.6

cleos push action puton addcmt '["curl", "0", "comment"]' -p curl
sleep 0.6
cleos push action puton addcmt '["tak", "1", "comment"]' -p tak
sleep 0.6

done