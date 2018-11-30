# puton_token

## refer
- https://eosio.stackexchange.com/questions/1448/how-to-access-multi-index-from-other-contract

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
- Argument: ["week"]
- deferred transaction에서 week + 1 하면서 호출
 
```sh
$ cleos push action puton.token reward '[0]' -p puton.token
```

##### PTN 토큰 생성(발행)

- Action Name: ```create```
- Argument: ["issuer", "총발행량 심볼"]

```
$ cleos push action puton.token create '["puton.token","1000000000000.000 PTN"]' -p puton.token
```

##### PTN 토큰 유통

- Action Name: ```issue```
- Argument: ["eos 유저", "발행량 PTN", "메모"]

```
$ cleos push action puton.token issue '["tak","100.000 PTN","memo"]' -p puton.token
$ cleos push action puton.token issue '["curl","100.000 PTN","memo"]' -p puton.token
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
$ cleos get table puton.token PTN stat
{
  "rows": [{
      "supply": "900.028 PTN",
      "max_supply": "1000000000000.000 PTN",
      "issuer": "puton.token"
    }
  ],
  "more": false
}

$ cleos get currency balance puton.token tak
90.000 PTN

$ cleos get currency balance puton.token curl
10.000 PTN
```


#### Jungle testnet 명령어 
 
##### Account
- esgfijifdgdf: 푸턴 서비스
  - EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
- dfgdfgf23asd: 푸턴 토큰 서비스
  - EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

- asas123fdfsa: 유저
- asas12fsddfs: 유저


##### Key
- EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

##### API Endpoint
- http://jungle.cryptolions.io:18888
- http://dev.cryptolions.io:38888
- https://jungle.eosio.cr:443
- http://jungle.cryptolions.io:18888
- http://dev.cryptolions.io:18888
- http://jungle.eosgen.io:80
- http://jungle.eosmeso.io:8888
- http://167.99.91.77:8888
- http://zztl1.f3322.net:6868
- http://zztl1.f3322.net:6868

##### Command

```
$ cleos -u http://dev.cryptolions.io:38888 get info

$ cleos -u http://dev.cryptolions.io:38888 set contract esgfijifdgdf ../puton
$ cleos -u http://dev.cryptolions.io:38888 set contract dfgdfgf23asd ../puton_token

$ cleos -u http://dev.cryptolions.io:38888 system buyram asas123fdfsa asas123fdfsa "100 EOS"
$ cleos -u http://dev.cryptolions.io:38888 system buyram dfgdfgf23asd dfgdfgf23asd "100 EOS"
$ cleos -u http://dev.cryptolions.io:38888 system buyram esgfijifdgdf esgfijifdgdf "100 EOS"
```

```
# create puton account 
$ cleos -u http://dev.cryptolions.io:38888 push action esgfijifdgdf createuser '["asas12fsddfs"]' -p asas12fsddfs
$ cleos -u http://dev.cryptolions.io:38888 push action esgfijifdgdf createuser '["asas123fdfsa"]' -p asas123fdfsa

# post 작성
$ cleos -u http://dev.cryptolions.io:38888 push action esgfijifdgdf addpost '['asas12fsddfs', "IPFS_ADDR_testtest"]' -p asas12fsddfs
$ cleos -u http://dev.cryptolions.io:38888 push action esgfijifdgdf addpost '['asas123fdfsa', "IPFS_ADDR_testtest"]' -p asas123fdfsa

# like post
$ cleos -u http://dev.cryptolions.io:38888 push action esgfijifdgdf likepost '["asas12fsddfs", "0"]' -p asas12fsddfs
$ cleos -u http://dev.cryptolions.io:38888 push action esgfijifdgdf likepost '["asas123fdfsa", "0"]' -p asas123fdfsa

# comment 작성
$ cleos -u http://dev.cryptolions.io:38888 push action esgfijifdgdf addcmt '["asas12fsddfs", '0', "comment_asas12fsddfs"]' -p asas12fsddfs
$ cleos -u http://dev.cryptolions.io:38888 push action esgfijifdgdf addcmt '["asas123fdfsa", '0', "asas123fdfsa"]' -p asas123fdfsa

# table 확인
$ cleos -u http://dev.cryptolions.io:38888 get table esgfijifdgdf esgfijifdgdf posts
```

```
# set PTN token
cleos -u http://dev.cryptolions.io:38888 set contract dfgdfgf23asd ../puton_token

cleos -u http://dev.cryptolions.io:38888 push action dfgdfgf23asd create '["dfgdfgf23asd","1000000000000.000 PTN"]' -p dfgdfgf23asd
cleos -u http://dev.cryptolions.io:38888 push action dfgdfgf23asd reward '[0]' -p dfgdfgf23asd

cleos -u http://dev.cryptolions.io:38888 push action dfgdfgf23asd issue '["asas12fsddfs","100000.000 PTN","memo"]' -p dfgdfgf23asd

cleos -u http://dev.cryptolions.io:38888 get currency balance dfgdfgf23asd asas12fsddfs
```