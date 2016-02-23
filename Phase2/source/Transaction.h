#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <iostream>
#include <string>
#include "TransactionMapper.h"

//Holds the constants for the maximum amount for transfer/paybill/withdrawal as well as the fees for student/non-student accounts
class Transaction{
 
 public:  
  //METHODS
  //Constructor that stores the transaction name/type, account name, number, amount, and any misc information relating to a particular transaction in the respective member variables 
  Transaction(std::string transaction_name,
			 std::string account_name,
			 std::string account_number,
			 std::string amount,
			 std::string misc);

  //Converts the current Transaction object into the properly formatted transaction string that will eventually be written to in the following format
  //02 tempname             12311 00099.99 A
  std::string to_string();
  
  //MEMBERS
  std::string transaction_code_; //the corresponding transaction code
  std::string account_name_; //the account holder name
  std::string account_number_; //the account number
  std::string amount_; //the amount involved in the transaction
  std::string misc_; //and misc data
  
};

#endif






























