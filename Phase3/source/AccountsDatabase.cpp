#include "AccountsDatabase.h"

AccountsDatabase::AccountsDatabase(std::string curr_bank_accounts_file_name){
  //begin reading in from current bank accounts file
  std::string line; //holds each read in line from the file
  std::ifstream input_file; //The current bank accounts file name
  input_file.open(curr_bank_accounts_file_name); //open the current bank accounts file for reading
  while(!input_file.eof()){
    //line is in the format: NNNNN_AAAAAAAAAAAAAAAAAAAA_S_UUUUUUUU_Q
    getline(input_file, line);
    // create an account based on the the string read in
    Account new_account_(line); //create a new account based on the line read in
    this->database_.push_back(new_account_); //add the account to the account database
  }
  input_file.close(); //close the file
}

bool AccountsDatabase::nameExists(std::string account_holder_name){
  return true;
}

bool AccountsDatabase::isValidAccount(std::string account_holder_name, std::string account_number){
  return true;
}





























