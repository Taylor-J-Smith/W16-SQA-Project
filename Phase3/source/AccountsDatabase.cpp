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
  for(std::vector<Account>::size_type i = 0; i != this->database_.size(); i++) {
    if (account_holder_name.compare(this->database_[i].name_) == 0){
      //found the account
      return true;
    }
  }
  //Did not find the account
  return false;
}

bool AccountsDatabase::isValidAccount(std::string account_holder_name, std::string account_number){
  for(std::vector<Account>::size_type i = 0; i != this->database_.size(); i++) {
    if (account_holder_name.compare(this->database_[i].name_) == 0){
      //found the account
      if (this->database_[i].number_.compare(account_number) == 0){
	return true;
      }else{
	return false;
      }
    }
  }
  //Did not find the account
  return false;  
}

std::string AccountsDatabase::getAccountNumber(std::string account_holder_name){
  for(std::vector<Account>::size_type i = 0; i != this->database_.size(); i++) {
    if (account_holder_name.compare(this->database_[i].name_) == 0){
      //found the account
      return this->database_[i].number_;
    }
  }
  //Did not find the account name 
  return "00000";
}

std::string AccountsDatabase::getAccountName(std::string account_number){
  for(std::vector<Account>::size_type i = 0; i != this->database_.size(); i++){
    if (account_number.compare(this->database_[i].number_) == 0){
      //found the account
      return this->database_[i].name_;
    }
  }
  //Did not find the account name 
  return "                    ";
}

Account AccountsDatabase::getAccountObject(std::string account_number){
  for(std::vector<Account>::size_type i = 0; i != this->database_.size(); i++){
    if (account_number.compare(this->database_[i].number_) == 0){
      //found the account
      return this->database_[i];
    }
  }  
}

//update the withdrawn_amount and the available_balance_ for the account with the withdrawn_instance
void AccountsDatabase::updateWithdrawnAmount(std::string account_number, std::string withdrawn_instance){
  for(std::vector<Account>::size_type i = 0; i != this->database_.size(); i++){
    if (account_number.compare(this->database_[i].number_) == 0){
      //found the account - update the account
      this->database_[i].withdrawn_amount_ += stof(withdrawn_instance); //update the withdrawn_amount_
      this->database_[i].available_balance_ -= stof(withdrawn_instance);//update the available_balance
      return;
    }
  }
  //Did not find the account - something went wrong
  std::cout << "[AccountsDatabase::updateWithdrawnAmount] did not find account" << std::endl;
}

//Check if the amount to be withdrawn is possible with that account's balance
bool AccountsDatabase::isWithdrawalPossible(std::string account_number,
					    std::string withdrawn_instance){
  for(std::vector<Account>::size_type i = 0; i != this->database_.size(); i++){
    if (account_number.compare(this->database_[i].number_) == 0){      
      //found the account - update the account
      float fee = 0.10;
      //check if it is a student account
      if (this->database_[i].plan_.compare("S") == 0){
	//is is a student account
	fee = 0.05;
      }

      //check if given the account balance the withdrawal is possible
      if ((roundf((this->database_[i].available_balance_ - stof(withdrawn_instance) - fee)*100)/100.0) < 0){
	//the user does not have the funds
	//std::cout << "TEMP:" << database_[i].available_balance_ - stof(withdrawn_instance) - fee << std::endl;
	return false;
      }else{
	return true;
      }
    }
  }
  //Did not find the account - something went wrong
  std::cout << "[AccountsDatabase::isWithdrawalPossible] did not find account" << std::endl;  
}


//Funciton not working
void AccountsDatabase::updateAccount(Account &updated_account){
  std::string account_number = updated_account.number_;
  for(std::vector<Account>::size_type i = 0; i != this->database_.size(); i++){
    if (account_number.compare(this->database_[i].number_) == 0){
      //found the account - update the account
      //this->database_[i] = updated_account;
    }
  }
  //Did not find the account - something went wrong
  std::cout << "[AccountsDatabase::updateAccount] did not find account" << std::endl;
}





















