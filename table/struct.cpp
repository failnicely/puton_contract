#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/print.h>
#include <eosiolib/transaction.hpp>
#include <string>
#include <vector>

// struct cmt for post_table
struct cmtrow
{
    uint16_t cmt_id = 0;
    account_name author = 0;
    std::string cmt_hash = "";
    time created_at = 0;
};

// @abi table users
struct user
{
    account_name account;
    std::vector<uint64_t> liked_rows;

    auto primary_key() const { return account; }

    EOSLIB_SERIALIZE(user, (account)(liked_rows))
};

// @abi table posts
struct post
{
    uint64_t id;
    account_name author;
    std::string ipfs_addr;
    std::vector<cmtrow> cmt_rows;
    uint16_t last_id; // for cmt_rows
    uint16_t like_cnt;
    uint16_t point;
    time created_at;

    auto primary_key() const { return id; }
    auto by_author() const { return author; }
    uint64_t by_created_at() const { return created_at; }

    EOSLIB_SERIALIZE(post, (id)(author)(ipfs_addr)(cmt_rows)(last_id)(like_cnt)(point)(created_at))
};
