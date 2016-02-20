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

std::string Transaction::to_string(){
  //create string to hold the properly formatted transaction string
  std::string transaction_string = "";
  transaction_string += this->transaction_code_;
  transaction_string += " ";

  std::string temp_name = this->account_name_;
  //pad the string
  while (temp_name.length() < 20){
    temp_name += " ";
  }
  transaction_string += temp_name;
  transaction_string += " ";
  
  transaction_string += this->account_number_;
  transaction_string += " ";
  
  //pad the amount with the appropriate amount of 0s
  std::string temp_amount = this->amount_;
  while (temp_amount.length() < 8){
    temp_amount = "0" + temp_amount;
  }
  transaction_string += temp_amount;
  transaction_string += " ";

  transaction_string += this->misc_;
  
  return transaction_string;
}




























