#include <string>
#include <vector>
#include <eosiolib/eosio.hpp> 

using namespace eosio; 

// struct post for user_table
struct postrow {
    uint64_t post_id = 0;
    // TODO: add additional variable
    // time liked_at = 0;
};

// struct cmt for post_table
struct cmtrow {
    uint16_t cmt_id = 0;
    account_name author = 0;
    std::string cmt_hash = "";
    time created_at = 0;
};

class puton_service: public eosio::contract {

    public: 
        puton_service(account_name self): contract::contract(self),
                                          user_table(self, self),
                                          post_table(self, self) {}

        /* 
         * USER ACTIONS
         */

        // @abi action 
        void createuser(const account_name account);

        /* 
         * POST ACTIONS
         */

        // @abi action 
        void addpost(const account_name author, const std::string ipfs_addr);

        // @abi action 
        void updatepost(const account_name author, const uint64_t id, const std::string ipfs_addr);

        // @abi action 
        void likepost(const account_name user, const uint64_t id);

        // @abi action 
        void cancellike(const account_name user, const uint64_t id);

         // @abi action
        void deletepost(const account_name author, const uint64_t id);

        /* 
         * COMMENT ACTIONS
         */

        // @abi action
        void addcmt(const account_name author, const uint64_t post_id, const std::string cmt_hash);

        // @abi action 
        void updatecmt(const account_name author, const uint64_t post_id, const uint16_t cmt_id, const std::string cmt_hash);

        // @abi action
        void deletecmt(const account_name author, const uint64_t post_id, const uint16_t cmt_id);
      
    private:

        // @abi table users 
        struct user {
            account_name account;
            std::vector<postrow> liked_rows;

            auto primary_key() const { return account; }

            EOSLIB_SERIALIZE(user, (account)(liked_rows))
        };

        // @abi table posts
        struct post {
            uint64_t id;
            account_name author;
            std::string ipfs_addr;
            std::vector<cmtrow> cmt_rows;
            uint16_t last_id; // for cmt_rows
            uint16_t like_cnt;
            uint16_t point;
            time created_at;

            auto primary_key() const { return id; }

            EOSLIB_SERIALIZE(post, (id)(author)(ipfs_addr)(cmt_rows)(last_id)(like_cnt)(point)(created_at))
        };

        // define tables
        multi_index<N(users), user> user_table;
        multi_index<N(posts), post> post_table;

        // private variable
        std::vector<postrow> empty_post_rows;
        std::vector<cmtrow> empty_cmt_rows;

        // private method
        int getIndex(const std::vector<postrow> &rows, const uint64_t id);
        int getIndex(const std::vector<cmtrow> &rows, const uint16_t cmt_id);
 };

EOSIO_ABI(puton_service, (createuser)(addpost)(updatepost)(likepost)(cancellike)(deletepost)(addcmt)(updatecmt)(deletecmt))