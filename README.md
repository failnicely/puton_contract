# puton

  <img alt="puton" title="puton" src="https://user-images.githubusercontent.com/7614353/47765294-a0af7700-dd0c-11e8-9348-511460dd8a38.png" width="300">

<br />

## Prerequisite

#### 1. Create wallet
```sh
$ cleos wallet create
"/usr/local/bin/keosd" launched
Creating wallet: default
Save password to use in the future to unlock this wallet.
Without password imported keys will not be retrievable.
"PW5KRyUSVq3Ytht2mwHNx5ZQWYWginSJkiEhU5n6LWL6ehattytK2"

$ cleos wallet create -n tak
Creating wallet: tak
Save password to use in the future to unlock this wallet.
Without password imported keys will not be retrievable.
"PW5KBvksXaoDgkQcCCnkFLbfxMUW5e5TK3hYZi5MhsW5duzzexdnV"
```

#### 2. Import Key
```sh
# Create key
$ cleos create key
Private key: 5JRoLzjFcpBpEUAR3nErMTjRozeonFjBCnfr35t5MC6tVWQdqyW
Public key: EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

$ cleos create key
Private key: 5Ja7N54Y9swFfFg4GgUWBBvAGz3jTKhpU5bEHxnFKpQELV5j5vV
Public key: EOS6BFKgddEY1BGQSouFAhh366hyETt6A4x25xdMakwXwsqkUiVop

# Import key
$ cleos wallet import 5JRoLzjFcpBpEUAR3nErMTjRozeonFjBCnfr35t5MC6tVWQdqyW
imported private key for: EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

$ cleos wallet import 5Ja7N54Y9swFfFg4GgUWBBvAGz3jTKhpU5bEHxnFKpQELV5j5vV
imported private key for: EOS6BFKgddEY1BGQSouFAhh366hyETt6A4x25xdMakwXwsqkUiVop
```

#### 3. Open & Unlock wallet
```sh
# Open wallet
$ cleos wallet open 
Opened: default

$ cleos wallet open -n tak
Opened: tak

# Unlock wallet
$ cleos wallet unlock --password PW5KRyUSVq3Ytht2mwHNx5ZQWYWginSJkiEhU5n6LWL6ehattytK2
Unlocked: default

$ cleos wallet unlock -n tak --password PW5KBvksXaoDgkQcCCnkFLbfxMUW5e5TK3hYZi5MhsW5duzzexdnV
Unlocked: tak
```

#### 4. Run nodeos
- Option
  - ```--delete-all-block```: delete all blocks
  - ```--contracts-console```: print degug message

```sh
$ nodeos -e -p eosio --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --delete-all-block --contracts-console
```

<br />

## How to use
Please refer below

- [puton](https://github.com/failnicely/puton_contract/blob/develop/puton/README.md)
- [puton.token](https://github.com/failnicely/puton_contract/blob/develop/puton_token/README.md) 

<br />

## Command for Jungle Testnet 2.0 

### Account
- puton123serv: puton contract
- dsnsdkasd234: puton.token contract
- 13dfdfgdfgdg: user
- ty3534543dfg: user

### Buy ram

```
$ cleos -u https://api.jungle.alohaeos.com:443 system buyram puton123serv puton123serv "100 EOS"
$ cleos -u https://api.jungle.alohaeos.com:443 system buyram dsnsdkasd234 dsnsdkasd234 "100 EOS"
$ cleos -u https://api.jungle.alohaeos.com:443 system buyram 13dfdfgdfgdg 13dfdfgdfgdg "100 EOS"
$ cleos -u https://api.jungle.alohaeos.com:443 system buyram ty3534543dfg ty3534543dfg "100 EOS"
```

### Set contract

```
$ cleos -u https://api.jungle.alohaeos.com:443 set contract puton123serv ../puton
$ cleos -u https://api.jungle.alohaeos.com:443 set contract dsnsdkasd234 ../puton_token
```

### Create user

```
$ cleos -u https://api.jungle.alohaeos.com:443 push action puton123serv createuser '["13dfdfgdfgdg"]' -p 13dfdfgdfgdg
$ cleos -u https://api.jungle.alohaeos.com:443 push action puton123serv createuser '["ty3534543dfg"]' -p ty3534543dfg
```

### Create post
```
$ cleos -u https://api.jungle.alohaeos.com:443 push action puton123serv addpost '['13dfdfgdfgdg', "IPFS_ADDR_testtest"]' -p 13dfdfgdfgdg
$ cleos -u https://api.jungle.alohaeos.com:443 push action puton123serv addpost '['13dfdfgdfgdg', "22222222222"]' -p 13dfdfgdfgdg
$ cleos -u https://api.jungle.alohaeos.com:443 push action puton123serv addpost '['ty3534543dfg', "3333333"]' -p ty3534543dfg
$ cleos -u https://api.jungle.alohaeos.com:443 push action puton123serv addpost '['ty3534543dfg', "444444"]' -p ty3534543dfg
```

### Add comment

```
$ cleos -u https://api.jungle.alohaeos.com:443 push action puton123serv addcmt '["13dfdfgdfgdg", '0', "commentecasddasdsa"]' -p 13dfdfgdfgdg
```

### Get table

```
$ cleos -u https://api.jungle.alohaeos.com:443 get table puton123serv puton123serv posts
```

### Token

```
# create token and start reward 
$ cleos -u https://api.jungle.alohaeos.com:443 push action dsnsdkasd234 create '["dsnsdkasd234","1000000000000.000 PTN"]' -p dsnsdkasd234
$ cleos -u https://api.jungle.alohaeos.com:443 push action dsnsdkasd234 reward '[0]' -p dsnsdkasd234

# issue token for test
$ cleos -u https://api.jungle.alohaeos.com:443 push action dsnsdkasd234 issue '["dsnsdkasd234","100000.000 PTN","memo"]' -p dsnsdkasd234
$ cleos -u https://api.jungle.alohaeos.com:443 get currency balance dsnsdkasd234 dsnsdkasd234
```

### RPC communication

```
$ curl -X POST https://api.jungle.alohaeos.com:443/v1/chain/get_table_rows -d '{"json":true,"code":"puton123serv","scope":"puton123serv","table":"posts", "index_position":3,"key_type":"i64","lower_bound":"ty3534543dfg","upper_bound":"ty3534543dfg"}'
$ curl -X POST https://api.jungle.alohaeos.com:443/v1/chain/get_table_rows -d '{"json":true,"code":"puton123serv","scope":"puton123serv","table":"posts", "index_position":3,"key_type":"i64","lower_bound":"13dfdfgdfgdg","upper_bound":"13dfdfgdfgdg"}'
```
