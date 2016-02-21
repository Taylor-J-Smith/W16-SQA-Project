#include "CreateHandler.h"

void CreateHandler::handle(Account current_account, 
				AccountsDatabase account_database,
				std::vector<Transaction> &session_transactions){
  
  //init the prompts
  std::string account_name_prompt = "[create] Enter the account holder name:";
  std::string init_balance_prompt = "[create] Enter the initial balance:";
  std::string success_prompt = "[create] Success!";
 
  std::string basic_prompt = ">> ";
  std::string account_name;
  std::string account_number = "00000";
  std::string init_balance;
  std::string misc = "A ";

  std::cout << account_name_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account_name; //take input from the user

  std::cout << init_balance_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> init_balance; //take input from the user

  //success message
  std::cout << success_prompt << std::endl;

  //TODO: update the accounts database in the frontend (not done in prototype)
  //make a new transaction
  Transaction new_transaction("create", account_name, account_number, init_balance, misc);
  session_transactions.push_back(new_transaction);
}
