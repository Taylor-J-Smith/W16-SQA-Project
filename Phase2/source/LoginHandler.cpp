#include "LoginHandler.h"

void LoginHandler::handle(Account current_account, 
				AccountsDatabase account_database,
				std::vector<Transaction> &session_transactions){
  
  //init the prompts
  std::string account_type_prompt = "[login] Enter the type of account:";
  std::string account_name_prompt = "[login] Enter the account holder name:";  
  std::string success_prompt = "[login] Success!";
 
  std::string basic_prompt = ">> ";
  std::string account_type;
  std::string account_name;
  std::string account_number = "12345"; //temp for prototype
  std::string amount = "00000.00";
  std::string misc = "S ";


  std::cout << account_type_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account_type; //take input from the user
  
  std::cout << account_name_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account_name; //take input from the user

  //success message
  std::cout << success_prompt << std::endl;

  //TODO: update the accounts database in the frontend (not done in prototype)
  //make a new transaction
  Transaction new_transaction("login", account_name, account_number, amount, misc);
  session_transactions.push_back(new_transaction);
}
