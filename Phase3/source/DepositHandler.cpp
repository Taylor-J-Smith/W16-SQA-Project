#include "DepositHandler.h"

void DepositHandler::handle(SessionStatus current_status, 
				AccountsDatabase account_database,
				std::vector<Transaction> &session_transactions){
  
	if(current_status.is_disabled){
		std::cout << "[deposit] ERROR: TRANSACTION NOT AVAILABLE WHILE ACCOUNT IS DISABLED" << std::endl;
		return;
	}
	
  //init the prompts
  std::string account_name_prompt = "[deposit] Enter the account holder name:";
  std::string account_number_prompt = "[deposit] Enter the account number:";
  std::string amount_prompt = "[deposit] Enter amount to deposit:";
  std::string success_prompt = "[deposit] Success!";

  //init all the variables that will hold user input data
  std::string basic_prompt = ">> ";
  std::string account_name;
  std::string account_number;
  std::string amount;
  std::string misc = "A ";

  if (current_status.is_admin){
    //Read in Account Name from the user
    std::cout << account_name_prompt << std::endl;
    std::cout << basic_prompt;
    std::cin.ignore();
    std::getline(std::cin, account_name);
    //pad the inputted account name to 20 characters with whitespace
    while (account_name.length() < 20){
      account_name += " ";
    }
  }else{
    account_name = current_status.account_name;
  }
  
  //Read in the Account Number
  std::cout << account_number_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account_number; //take input from the user


  //check if account number matches the user
  if (!account_database.isValidAccount(account_name, account_number)){
    //std::cout << current_status.account_name << ":::" << account_number << std::endl;
    std::cout << "[withdrawal] ERROR: ACCOUNT # DOES NOT MATCH HOLDER" << std::endl;
    return;
  }
  
  if(account_database.getAccountObject(account_number).status_.compare("D") == 0){
    std::cout << "[deposit] ERROR: TRANSACTION NOT AVAILABLE WHILE ACCOUNT IS DISABLED" << std::endl;
    return;
  }

  if(account_database.getAccountObject(account_number).deleted_){
    std::cout << "[deposit] ERROR: ACCOUNT NOT FOUND" << std::endl;
    return;
  }

  //Read in the Amount
  std::cout << amount_prompt << std::endl;
  std::cout << basic_prompt;    
  std::cin >> amount; //take input from the user

  //verify that the user enterd a properly formated amount
  if (!CommandValidator::validateAmountFormat(amount)){
    std::cout << "[withdrawal] ERROR: INVALID INPUT" << std::endl;
    return;
  }
  //success message
  std::cout << success_prompt << std::endl;

  //TODO: update the accounts database in the frontend (not done in prototype)
  //make a new transaction
  Transaction new_transaction("deposit", account_name, account_number, amount, misc);
  session_transactions.push_back(new_transaction);
}
