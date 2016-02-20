#include "Transaction.h"

Transaction::Transaction(std::string transaction_name,
			 std::string account_name,
			 std::string account_number,
			 std::string amount,
			 std::string misc){

  TransactionMapper transaction_map;
  this->transaction_code_ = transaction_map.map_[transaction_name];
  this->account_name_ = account_name;
  this->account_number_ = account_number;
  this->amount_ = amount;
  this->misc_ = misc;  
}




























