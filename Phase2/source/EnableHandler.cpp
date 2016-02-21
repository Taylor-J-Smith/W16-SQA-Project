#include "EnableHandler.h"

void EnableHandler::handle(Account current_account, 
				AccountsDatabase account_database,
				std::vector<Transaction> &session_transactions){
  
  //init the prompts
  std::string account_name_prompt = "[enable] Enter the account holder name:";
  std::string account_number_prompt = "[enable] Enter the account number:";
  std::string success_prompt = "[enable] Success!";
 
  std::string basic_prompt = ">> ";
  std::string account_name;
  std::string account_number;
  std::string amount = "00000.00";
  std::string misc = "A ";

  std::cout << account_name_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account_name; //take input from the user

  std::cout << account_number_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account_number; //take input from the user

  //success message
  std::cout << success_prompt << std::endl;

  //TODO: update the accounts database in the frontend (not done in prototype)
  //make a new transaction
  Transaction new_transaction("enable", account_name, account_number, amount, misc);
  session_transactions.push_back(new_transaction);
}