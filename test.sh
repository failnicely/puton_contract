#!/bin/bash

i="0"

while [ : ]
do

# create post
cleos push action puton addpost '["tak", "TAK_IPFS_ADDR"]' -p tak
sleep 0.6
# add comment
cleos push action puton addcmt '["curl", '$i', "comment_curl"]' -p curl
sleep 0.6
cleos push action puton addcmt '["camry", '$i', "comment_curl"]' -p camry
sleep 0.6
cleos push action puton addcmt '["jinny", '$i', "comment_curl"]' -p jinny
sleep 0.6
cleos push action puton addcmt '["uni", '$i', "comment_curl"]' -p uni
sleep 0.6
# like post
cleos push action puton likepost '["curl", '$i', "0"]' -p curl
sleep 0.6
cleos push action puton likepost '["camry", '$i', "0"]' -p camry
sleep 0.6
cleos push action puton likepost '["jinny", '$i', "0"]' -p jinny
sleep 0.6
cleos push action puton likepost '["uni", '$i', "0"]' -p uni
sleep 0.6

# create post
cleos push action puton addpost '["curl", "CURL_IPFS_ADDR"]' -p curl
sleep 0.6
# add comment
cleos push action puton addcmt '["tak", '$[$i+1]', "comment_curl"]' -p tak
sleep 0.6
cleos push action puton addcmt '["camry", '$[$i+1]', "comment_curl"]' -p camry
sleep 0.6
cleos push action puton addcmt '["jinny", '$[$i+1]', "comment_curl"]' -p jinny
sleep 0.6
cleos push action puton addcmt '["uni", '$[$i+1]', "comment_curl"]' -p uni
sleep 0.6
# like post
cleos push action puton likepost '["tak", '$[$i+1]']' -p tak
sleep 0.6
cleos push action puton likepost '["camry", '$[$i+1]']' -p camry
sleep 0.6
cleos push action puton likepost '["jinny", '$[$i+1]']' -p jinny
sleep 0.6
cleos push action puton likepost '["uni", '$[$i+1]']' -p uni
sleep 0.6

i=$[$i+1]
done