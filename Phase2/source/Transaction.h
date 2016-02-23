#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <iostream>
#include <string>
#include "TransactionMapper.h"

//Holds the constants for the maximum amount for transfer/paybill/withdrawal as well as the fees for student/non-student accounts
class Transaction{
 
 public:  
  //METHODS
  //constructor
  //Stores the transaction name/type, account name, number, amount, and any misc information relating to a particular transaction in the respective member variables
  Transaction(std::string transaction_name,
			 std::string account_name,
			 std::string account_number,
			 std::string amount,
			 std::string misc);

  //Prints the current transaction in the format:
  //02 tempname             12311 00099.99 A 
  std::string to_string();
  
  //MEMBERS
  std::string transaction_code_;
  std::string account_name_;
  std::string account_number_;
  std::string amount_;
  std::string misc_;
  
};

#endif






























