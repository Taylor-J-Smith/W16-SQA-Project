#include "DisableHandler.h"

void DisableHandler::handle(SessionStatus &current_status, 
				AccountsDatabase &account_database,
				std::vector<Transaction> &session_transactions){
  
  //init the prompts
  std::string account_name_prompt = "[disable] Enter the account holder name:";
  std::string account_number_prompt = "[disable] Enter the account number:";
  std::string success_prompt = "[disable] Success!";

  //Init all the variables that will hold user input data
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
		std::cout << "[disable] ERROR: USERNAME DOES NOT EXIST" << std::endl;
		return;
	}  
	
	//Read in the account number from the user
	std::cout << account_number_prompt << std::endl;
	std::cout << basic_prompt;
	std::cin >> account_number; //take input from the user

	if(!account_database.isValidAccount(account_name, account_number)){
		std::cout << "[disable] ERROR: ACCOUNT # DOES NOT MATCH HOLDER" << std::endl;
		return;
	}
	
	if(account_database.getAccountObject(account_number).status_.compare("D") == 0){
		std::cout << "[disable] ERROR: ACCOUNT ALREADY DISABLED" << std::endl;
		return;
	}
	
	if(account_database.getAccountObject(account_number).deleted_){
		std::cout << "[disable] ERROR: ACCOUNT NOT FOUND" << std::endl;
		return;
	}

  //success message
  std::cout << success_prompt << std::endl;

	DisableHandler::disableAccount(account_database, account_number);

  //make a new transaction
  Transaction new_transaction("disable", account_name, account_number, amount, misc);
  session_transactions.push_back(new_transaction);
}

void DisableHandler::disableAccount(AccountsDatabase &account_database,
					     											std::string account_number){
  for(std::vector<Account>::size_type i = 0; i != account_database.database_.size(); i++){
    if (account_number.compare(account_database.database_[i].number_) == 0){
      //found the account - update the account
      account_database.database_[i].status_ = "D";
      return;
    }
  }
  //Did not find the account - something went wrong
  std::cout << "[DiasableHandler::disableAccount] did not find account" << std::endl;
}
