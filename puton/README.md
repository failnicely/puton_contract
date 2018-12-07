# puton_contract

## How To Use

#### EOS 어카운트 생성

```sh
# Create account for puton
$ cleos create account eosio puton EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

# Create account for eos user
$ cleos create account eosio tak EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
$ cleos create account eosio curl EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
```

#### 스마트 컨트랙트 빌드 & 계정에 셋업

```sh
# build.sh [account_name] [contract_name]
$ ./build.sh puton puton
```

#### 액션 리스트

##### puton 유저 생성

- Action Name: ```createuser```
- Argument: ["EOS 유저"]

```sh
# Create new puton user
$ cleos push action puton createuser '["tak"]' -p tak
$ cleos push action puton createuser '["curl"]' -p curl
```

##### Post 작성

- Action Name: ```addpost```
- Param: ["PUTON 유저", "IPFS 데이터(포스트 관련 내용)"]
- post_id는 자동 생성됨

```sh
$ cleos push action puton addpost '["tak", "TAK_IPFS_ADDR_1"]' -p tak
$ cleos push action puton addpost '["tak", "TAK_IPFS_ADDR_2"]' -p tak
$ cleos push action puton addpost '["curl", "CURL_IPFS_ADDR_1"]' -p curl
$ cleos push action puton addpost '["curl", "CURL_IPFS_ADDR_2"]' -p curl
```

##### Post 업데이트

- Action Name: ```updatepost```
- Param: ["POST 작성자", "POST ID", "업데이트할 IPFS"]
- 액션 날린 유저가 업데이트할 post의 author가 아니면 에러

```sh
$ cleos push action puton updatepost '["tak", "1", "TAK_UPDATED"]' -p tak
$ cleos push action puton updatepost '["curl", "3", "CURL_UPDATED"]' -p curl
```

##### Post 좋아요

- Action Name: ```likepost```
- Param: ["PUTON 유저", "좋아요할 POST ID"]

```sh
$ cleos push action puton likepost '["tak", "2"]' -p tak
$ cleos push action puton likepost '["curl", "1"]' -p curl
$ cleos push action puton likepost '["curl", "2"]' -p curl
```

##### Post by author

- Action Name: ```postsbyuser```
- Param: ["PUTON 유저"]

```sh
$ cleos push action puton postsbyuser '["tak"]' -p tak
$ cleos push action puton postsbyuser '["curl"]' -p curl
```

##### 좋아요 취소

- Action Name: ```cancellike```
- Param: ["PUTON 유저", "취소할 POST ID"]

```sh
$ cleos push action puton cancellike '["tak", "2"]' -p tak
$ cleos push action puton cancellike '["curl", "2"]' -p curl
```

##### POST 삭제

- Action Name: ```deletepost```
- Param: ["POST 작성자", "삭제할 POST ID"]
- 작성자가 아니면 POST 삭제 못함 

```sh
$ cleos push action puton deletepost '["tak", "1"]' -p tak
$ cleos push action puton deletepost '["curl", "2"]' -p curl
```

##### COMMENT 작성

- Action Name: ```addcmt```
- Param: ["COMMENT 작성자", "코멘트 작성할 POST ID", "코멘트 내용"]

```sh
$ cleos push action puton addcmt '["tak", "3", "comment"]' -p tak
$ cleos push action puton addcmt '["curl", "3", "comment"]' -p curl
```

##### COMMENT 업데이트

- Action Name: ```updatecmt```
- Param: ["COMMENT 작성자", "POST ID", "COMMENT ID", "업데이트할 내용"]
- 코멘트 작성자가 아니면 업데이트 못함

```sh
$ cleos push action puton updatecmt '["tak", "3", "1", "updated comment"]' -p tak
$ cleos push action puton updatecmt '["curl", "3", "2", "updated comment"]' -p curl
```

##### COMMENT 삭제

- Action Name: ```deletecmt```
- Param: ["COMMENT 작성자", "POST ID", "COMMENT ID"]

```sh
$ cleos push action puton deletecmt '["tak", "2", "1"]' -p tak
$ cleos push action puton deletecmt '["curl", "2", "2"]' -p curl
```

#### DB 쿼리

##### 유저 테이블
```sh
$ cleos get table puton puton users
{
  "rows": [{
      "account": "curl",
      "liked_rows": [{
          "post_id": 4
        }
      ]
    },{
      "account": "tak",
      "liked_rows": [{
          "post_id": 2
        }
      ]
    }
  ],
  "more": false
}
```

##### POST 테이블

```
$ cleos get table puton puton posts --lower "10" --upper "20"

$ cleos get table puton puton posts
{
  "rows": [{
      "id": 0,
      "author": "tak",
      "ipfs_addr": "TEST1111",
      "cmt_rows": [],
      "last_id": 0,
      "like_cnt": 0,
      "point": 0,
      "created_at": 1540951254
    },{
      "id": 4,
      "author": "curl",
      "ipfs_addr": "CURL_IPFS_ADDR_1",
      "cmt_rows": [{
          "cmt_id": 2,
          "author": "tak",
          "cmt_hash": "comment",
          "created_at": 1540952369
        }
      ],
      "last_id": 3,
      "like_cnt": 1,
      "point": 2,
      "created_at": 1540951835
    },{
      "id": 5,
      "author": "curl",
      "ipfs_addr": "CURL_IPFS_ADDR_1",
      "cmt_rows": [],
      "last_id": 0,
      "like_cnt": 0,
      "point": 0,
      "created_at": 1540951837
    }
  ],
  "more": false
}
```