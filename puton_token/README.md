# puton_token

## error
> abi 제대로 생성 안되는 이슈
> https://github.com/EOSIO/eosio.cdt -> 설치 후 cdt로 빌드
> refer: https://github.com/EOSIO/eos/issues/4636

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

##### Reward (deferred)

- Action Name: ```reward```
- Argument: [""]

```sh
$ cleos push action puton.token reward '[""]' -p puton.token
```

##### PTN 토큰 생성(발행)

- Action Name: ```create```
- Argument: ["eosio", "총 발행량", "토큰 심볼"]

```
$ cleos push action puton.token create '["eosio","1000000000000.000 PTN"]' -p puton.token
```

##### PTN 토큰 유통

- Action Name: ```issue```
- Argument: ["eos 유저", "발행량 PTN", "메모"]

```
$ cleos push action puton.token issue '["tak","100.000 PTN","memo"]' -p eosio
$ cleos push action puton.token issue '["curl","100.000 PTN","memo"]' -p eosio
```

##### 토큰 transfer 

- Action Name: ```issue```
- Argument: ["From", "To", "토큰량", "메모"]

```
$ cleos push action puton.token transfer '{"from":"tak","to":"curl","quantity":"10.000 PTN","memo":"memo"}' -p tak
$ cleos push action puton.token transfer '["tak","curl","10.000 PTN","memo"]' -p tak
```

##### 토큰 확인

```
$ cleos get currency balance puton.token tak
$ cleos get currency balance puton.token curl
```