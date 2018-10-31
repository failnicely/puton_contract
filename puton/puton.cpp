#include<puton.hpp>

const uint64_t THREE_DAYS = 3 * 86400; // 3 days
// const uint64_t THREE_DAYS = 3 * 60; // 3 minutes

/// USER ACTIONS
void puton_service::createuser(const account_name account)
{
    // check account auth
    require_auth(account);

    // check account on user_table
    auto itr = user_table.find(account);
    eosio_assert(itr == user_table.end(), "UserTable already has a user");

    // create user
    user_table.emplace(_self, [&](auto& u) {
        u.account = account;
        u.liked_rows = empty_post_rows;
    });

    // debug print
    print(name{account}, " user created");
}

/// POST ACTIONS
void puton_service::addpost(const account_name user, const std::string ipfs_addr)
{
    // check user permission
    require_auth(user);

    // check account on user_table
    auto user_itr = user_table.find(user);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // get unique post_id from post_table
    uint64_t post_id = post_table.available_primary_key();

    // create post to post_table
    post_table.emplace(_self, [&](auto& p) {
        p.id = post_id;
        p.author = user;
        p.ipfs_addr = ipfs_addr;
        p.cmt_rows = empty_cmt_rows;
        p.last_id = 0;
        p.like_cnt = 0;
        p.point = 0;
        p.created_at = now();
    });

    // debug print
    print("post#", post_id, " created");
}

void puton_service::updatepost(const account_name author, const uint64_t id, const std::string ipfs_addr)
{
    // check user permission
    require_auth(author);

    // check account on user_table
    auto user_itr = user_table.find(author);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // check post on post_table
    auto post_itr = post_table.find(id);
    eosio_assert(post_itr != post_table.end(), "PostTable does not has id");

    // check author
    bool is_author = post_itr->author == author;
    eosio_assert(is_author, "Not the author of this post");

    // update post_table
    post_table.modify(post_itr, _self, [&](auto &post) {
        post.ipfs_addr = ipfs_addr;
    });

    // debug print
    print("post#", id, " updated");
}

void puton_service::likepost(const account_name user, const uint64_t id)
{
    // check user permission
    require_auth(user);

    // check post on post_table
    auto post_itr = post_table.find(id);
    eosio_assert(post_itr != post_table.end(), "PostTable does not has id");

    // check account on user_table
    auto user_itr = user_table.find(user);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // check liked
    int likedIndex = getIndex(user_itr->liked_rows, id);
    eosio_assert(likedIndex == -1, "already liked");

    // update post_table
    post_table.modify(post_itr, _self, [&](auto &post) {
        post.like_cnt = post.like_cnt + 1;

        // calculate time range
        bool is_author = (user == post.author);
        bool is_compensation_period = (post.created_at + THREE_DAYS > now());

        if (!is_author && is_compensation_period) {
            post.point = post.point + 1;
        }
    });

    // update post_id to user's liked_rows 
    postrow row;
    user_table.modify(user_itr, _self, [&](auto& user) {
        row.post_id = id;
        user.liked_rows.push_back(row);
    });

    // debug print
    print("post#", id, " liked");
}

void puton_service::cancellike(const account_name user, const uint64_t id)
{
    // check user permission
    require_auth(user);

    // check post on post_table
    auto post_itr = post_table.find(id);
    eosio_assert(post_itr != post_table.end(), "PostTable does not has id");

    // check account on user_table
    auto user_itr = user_table.find(user);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // check liked
    int likedIndex = getIndex(user_itr->liked_rows, id);
    eosio_assert(likedIndex != -1, "The user did not like this post");

    // update liked_rows of user
    user_table.modify(user_itr, _self, [&](auto &user) {
        user.liked_rows.erase(user.liked_rows.begin() + likedIndex);
    });

    // update post_table
    post_table.modify(post_itr, _self, [&](auto &post) {
        post.like_cnt = post.like_cnt - 1;

        // calculate time range
        bool is_author = (user == post.author);
        bool is_compensation_period = (post.created_at + THREE_DAYS > now());

        if (!is_author && is_compensation_period) {
            post.point = post.point - 1;
        }
    });

    // debug print
    print("cancel like post#", id);
}

void puton_service::deletepost(const account_name author, const uint64_t id)
{
    // check user permission
    require_auth(author);

    // check account on user_table
    auto user_itr = user_table.find(author);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // check id on post_table
    auto itr = post_table.find(id);
    eosio_assert(itr != post_table.end(), "PostTable does not has id");

    // check author
    bool is_author = (itr->author == author);
    eosio_assert(is_author, "Not the author of this post");

    // delete post
    post_table.erase(itr);

    // debug print
    print("post#", id, " deleted");
}

/// COMMENT ACTION
void puton_service::addcmt(const account_name author, const uint64_t post_id, const std::string cmt_hash)
{
    // check user permission
    require_auth(author);

    // check account on user_table
    auto user_itr = user_table.find(author);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // check id on post_table
    auto itr = post_table.find(post_id);
    eosio_assert(itr != post_table.end(), "PostTable does not has id");

    // set cmtrow
    cmtrow row;
    row.author = author;
    row.cmt_hash = cmt_hash;
    row.created_at = now();

    // add cmt to post row
    post_table.modify(itr, _self, [&](auto &post) {
        row.cmt_id = post.last_id + 1;
        post.last_id = row.cmt_id;
        post.cmt_rows.push_back(row);

        // add point to post 
        bool is_author = (author == post.author);
        bool is_compensation_period = (post.created_at + THREE_DAYS > now());

        if (!is_author && is_compensation_period) {
            post.point = post.point + 1;
        }
    });

    print("comment added to post#", itr->id);
}

void puton_service::updatecmt(const account_name author, const uint64_t post_id, const uint16_t cmt_id, const std::string cmt_hash)
{
    // check user permission
    require_auth(author);

    // check account on user_table
    auto user_itr = user_table.find(author);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // check id on post_table
    auto itr = post_table.find(post_id);
    eosio_assert(itr != post_table.end(), "PostTable does not has id");

    // update cmt row
    post_table.modify(itr, _self, [&](auto &post) {
        // check cmt index
        int cmt_idx = getIndex(post.cmt_rows, cmt_id);
        eosio_assert(cmt_idx != -1, "Could not found cmt");

        // check author
        eosio_assert(post.cmt_rows[cmt_idx].author == author, "Not the author of this cmt");

        post.cmt_rows[cmt_idx].cmt_hash = cmt_hash;
    });

    // debug print
    print("comment updated");
}

void puton_service::deletecmt(const account_name author, const uint64_t post_id, const uint16_t cmt_id)
{
    // check user permission
    require_auth(author);

    // check account on user_table
    auto user_itr = user_table.find(author);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // check id on post_table
    auto itr = post_table.find(post_id);
    eosio_assert(itr != post_table.end(), "PostTable does not has id");

    // update cmt row
    post_table.modify(itr, _self, [&](auto &post) {
        int cmt_idx = getIndex(post.cmt_rows, cmt_id);
        eosio_assert(cmt_idx != -1, "Could not found cmt");

        // check cmt author
        eosio_assert(post.cmt_rows[cmt_idx].author == author, "Not the author of this cmt");
        post.cmt_rows.erase(post.cmt_rows.begin() + cmt_idx);

        // subtract point
        bool is_author = (author == post.author);
        bool is_compensation_period = (post.created_at + THREE_DAYS > now());

        if (!is_author && is_compensation_period) {
            post.point = post.point - 1;
        }
    });

    // debug print
    print("comment deleted");
}

// Private Functions

int puton_service::getIndex(const std::vector<postrow> &rows, const uint64_t id)
{
    // binary search
    int left = 0;
    int right = rows.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (rows[mid].post_id < id) {
            left = mid + 1;
        } else if (id < rows[mid].post_id) {
            right = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}

int puton_service::getIndex(const std::vector<cmtrow> &rows, const uint16_t cmt_id)
{
    // binary search
    int left = 0;
    int right = rows.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (rows[mid].cmt_id < cmt_id) {
            left = mid + 1;
        } else if (cmt_id < rows[mid].cmt_id) {
            right = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}
