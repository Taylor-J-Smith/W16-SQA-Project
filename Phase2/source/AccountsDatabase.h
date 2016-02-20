#ifndef ACCOUNTSDATABASE_H_
#define ACCOUNTSDATABASE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Account.h"

//Data Structure containing all accounts and helper methods 
class AccountsDatabase{
 public:
  //CONSTANTS

  //METHODS
  //constructor
  AccountsDatabase(std::string curr_bank_accounts_file_name);
  //checks if an account name exists in the database, and returns true if so, otherwise returns false  
  bool nameExists(std::string account_holder_name);
  //Checks to see if both the account name and number match the same account, returns true if they do, false otherwise
  bool isValidAccount(std::string account_holder_name, std::string account_number);
  
  //MEMBERS
  std::vector<Account> database_;
  
};

#endif






























