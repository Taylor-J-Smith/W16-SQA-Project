#include "EnableHandler.h"

void EnableHandler::handle(SessionStatus &current_status, 
				AccountsDatabase &account_database,
				std::vector<Transaction> &session_transactions){
  
  //init the prompts
  std::string account_name_prompt = "[enable] Enter the account holder name:";
  std::string account_number_prompt = "[enable] Enter the account number:";
  std::string success_prompt = "[enable] Success!";

  //init all the variables that will hold user input data
  std::string basic_prompt = ">> ";
  std::string account_name;
  std::string account_number;
  std::string amount = "00000.00";
  std::string misc = "A ";

	//Read in the Account Name from the user
  std::cout << account_name_prompt << std::endl;
  std::cout << basic_prompt;
	std::cin.ignore();
	std::getline(std::cin, account_name);
	//pad the inputted account name to 20 characters with whitespace
	while (account_name.length() < 20){
		account_name += " ";
	}

	if(!account_database.nameExists(account_name)){
		std::cout << "[enable] ERROR: USERNAME DOES NOT EXIST" << std::endl;
		return;
	}  
	
  //Read in the account number from the user
  std::cout << account_number_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account_number; //take input from the user

	if(!account_database.isValidAccount(account_name, account_number)){
		std::cout << "[enable] ERROR: ACCOUNT # DOES NOT MATCH HOLDER" << std::endl;
		return;
	}
	
	if(account_database.getAccountObject(account_number).status_.compare("A") == 0){
		std::cout << "[enable] ERROR: ACCOUNT ALREADY ENABLED" << std::endl;
		return;
	}
	
	if(account_database.getAccountObject(account_number).deleted_){
		std::cout << "[withdrawal] ERROR: ACCOUNT NOT FOUND" << std::endl;
		return;
	}

  //success message
  std::cout << success_prompt << std::endl;

	enableAccount(account_database, account_number);

  //TODO: update the accounts database in the frontend (not done in prototype)
  //make a new transaction
  Transaction new_transaction("enable", account_name, account_number, amount, misc);
  session_transactions.push_back(new_transaction);
}

void EnableHandler::enableAccount(AccountsDatabase &account_database,
					     											std::string account_number){
  for(std::vector<Account>::size_type i = 0; i != account_database.database_.size(); i++){
    if (account_number.compare(account_database.database_[i].number_) == 0){
      //found the account - update the account
      account_database.database_[i].status_ = "A";
      return;
    }
  }
  //Did not find the account - something went wrong
  std::cout << "[EnableHandler::enableAccount] did not find account" << std::endl;
}
