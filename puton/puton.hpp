#include "../table/struct.cpp"

using namespace eosio;

class puton_service : public eosio::contract
{

public:
  puton_service(account_name self) : contract::contract(self),
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
  // define tables
  multi_index<N(users), user> user_table;
  // multi_index<N(posts), post> post_table;
  multi_index<N(posts), post, indexed_by<N(created_at), const_mem_fun<post, uint64_t, &post::by_created_at>>> post_table;

  // private variable
  std::vector<postrow> empty_post_rows;
  std::vector<cmtrow> empty_cmt_rows;

  // private method
  int getIndex(const std::vector<postrow> &rows, const uint64_t id);
  int getIndex(const std::vector<cmtrow> &rows, const uint16_t cmt_id);
};

EOSIO_ABI(puton_service, (createuser)(addpost)(updatepost)(likepost)(cancellike)(deletepost)(addcmt)(updatecmt)(deletecmt))