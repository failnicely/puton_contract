#!/bin/bash

if [[ $# -ne 2 ]]; then
    echo "USAGE: build.sh <account_name> <contract_name> from within the directory"
    exit 1
fi

ACCOUNT=$1
CONTRACT=$2

eosiocpp -o ${CONTRACT}.wast ${CONTRACT}.cpp &&
eosiocpp -g ${CONTRACT}.abi ${CONTRACT}.hpp &&
cleos set contract ${ACCOUNT} ../${CONTRACT}
