#ifndef ACCOUNTSDATABASE_H_
#define ACCOUNTSDATABASE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Account.h"
#include <math.h>

//Data Structure containing all accounts and helper methods 
class AccountsDatabase{
 public:
  //METHODS
  //Constructor that takes in the current bank account file for the day and populates an internal datastructure that holds all Account Classes
  AccountsDatabase(std::string curr_bank_accounts_file_name);
  //Checks to see if the given account name exists in the database, if it does it returns true, otherwise it returns false
  bool nameExists(std::string account_holder_name);
  //Checks that the given account name and number correspond to the same account in the database, returns true if theu do, false otherwise
  bool isValidAccount(std::string account_holder_name, std::string account_number);
  //Returns an account name based on the given number
  std::string getAccountName(std::string account_number);
  //Returns the account number based on the account name that is given as a parameter
  std::string getAccountNumber(std::string account_holder_name);
  //Returns the Account object based on the the account_number given
  Account getAccountObject(std::string account_number);
  //Replaces an account in the database based on the provided account
  void updateAccount(Account &updated_account);
    
  //MEMBERS
  //A vector of accounts that are populated at the start of each day from the current bank accounts file
  std::vector<Account> database_;
  
};

#endif






























