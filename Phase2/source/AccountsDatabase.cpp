#include "AccountsDatabase.h"

AccountsDatabase::AccountsDatabase(std::string curr_bank_accounts_file_name){
  //begin reading in from current bank accounts file
  std::cout <<"Reading in " + curr_bank_accounts_file_name << std::endl;
  std::string line;
  std::ifstream input_file;
  input_file.open(curr_bank_accounts_file_name);
  while(!input_file.eof()){
    //line is in the format: NNNNN_AAAAAAAAAAAAAAAAAAAA_S_UUUUUUUU_Q
    getline(input_file, line);
    //std::cout << line << std::endl; //temp
    // create an account based on the the string read in
    Account new_account_(line); 
    this->database_.push_back(new_account_);
    std::cout << "Account \"" << new_account_.name_ << "\" added to Database!"<< std::endl;
  }
  input_file.close();
}

bool AccountsDatabase::nameExists(std::string account_holder_name){
  return true;
}

bool AccountsDatabase::isValidAccount(std::string account_holder_name, std::string account_number){
  return true;
}





























