#!/bin/bash

if [[ $# -ne 2 ]]; then
    echo "USAGE: build.sh <account_name> <contract_name> from within the directory"
    exit 1
fi

ACCOUNT=$1
CONTRACT=$2

if docker ps | grep eosio ; then
    echo "using docker"
    CLEOS='docker exec -it eosio /opt/eosio/bin/cleos --url http://127.0.0.1:7777 --wallet-url http://127.0.0.1:5555'
    EOSIOCPP='docker exec -it eosio /opt/eosio/tools/eosiocpp'  
    DOCKER_BASE_PATH='/contracts/puton_contract/'

    docker cp ../ eosio:/contracts/
    
    $EOSIOCPP -o ${DOCKER_BASE_PATH}puton/${CONTRACT}.wast ${DOCKER_BASE_PATH}puton/${CONTRACT}.cpp &&
    $EOSIOCPP -g ${DOCKER_BASE_PATH}puton/${CONTRACT}.abi ${DOCKER_BASE_PATH}puton/${CONTRACT}.hpp
    $CLEOS set contract ${ACCOUNT} ${DOCKER_BASE_PATH}${CONTRACT}
else
    eosiocpp -o ${CONTRACT}.wast ${CONTRACT}.cpp &&
    eosiocpp -g ${CONTRACT}.abi ${CONTRACT}.hpp &&
    cleos set contract ${ACCOUNT} ../${CONTRACT}
fi
