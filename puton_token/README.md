# puton_token

## Prerequisite
- please see README.md on puton dir

## How To Use

#### EOS 어카운트 생성

```sh
# Create account for puton
$ cleos create account eosio puton.token EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

# Set permission for inline action, deferred transaction
$ cleos set account permission puton.token active '{"threshold": 1,"keys": [{"key": "EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8","weight": 1}],"accounts": [{"permission":{"actor":"puton.token","permission":"eosio.code"},"weight":1}]}' owner -p puton.token

```

#### 스마트 컨트랙트 빌드 & 계정에 셋업

```sh
# build.sh [account_name] [contract_name]
$ ./build.sh puton.token puton_token
```

#### 액션 리스트

##### Read db from puton table

- Action Name: ```readdb```
- Argument: [""]

```sh
$ cleos push action puton.token readdb '[""]' -p puton.token
```

##### Start puton.token server

- Action Name: ```startserver```
- Argument: [""]

```sh
$ cleos push action puton.token readdb '[""]' -p puton.token
```