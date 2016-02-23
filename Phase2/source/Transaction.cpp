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
  //create string to hold the properly formatted transaction string in the following format:
  //10 test_trans           01234 00005.00 no
  std::string transaction_string = "";
  transaction_string += this->transaction_code_;
  transaction_string += " ";

  std::string temp_name = this->account_name_; //the unpadded account name
  //pad the string to 20 characters
  while (temp_name.length() < 20){
    temp_name += " ";
  }
  //add space after the account name
  transaction_string += temp_name;
  transaction_string += " ";

  //add space after the account number
  transaction_string += this->account_number_;
  transaction_string += " ";
  
  //pad the amount with up to 8 0s to the left
  std::string temp_amount = this->amount_;
  while (temp_amount.length() < 8){
    temp_amount = "0" + temp_amount;
  }
  //add space after the amount
  transaction_string += temp_amount;
  transaction_string += " ";

  //add the misc
  transaction_string += this->misc_;

  //return the final complete transaction string in the proper format
  return transaction_string;
}




























