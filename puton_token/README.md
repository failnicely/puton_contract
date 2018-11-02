# puton_token

## Prerequisite
- please see README.md on puton dir

## How To Use

#### EOS 어카운트 생성

```sh
# Create account for puton
$ cleos create account eosio puton.token EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
```

#### 스마트 컨트랙트 빌드 & 계정에 셋업

```sh
# build.sh [account_name] [contract_name]
$ ./build.sh puton.token puton_token
```

#### 액션 리스트

##### Read db from puton table

- Action Name: ```read```
- Argument: [""]

```sh
$ cleos push action puton.token read '[""]' -p puton.token
```