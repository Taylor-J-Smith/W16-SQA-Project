#include "WithdrawalHandler.h"

void WithdrawalHandler::handle(Account current_account, 
				AccountsDatabase account_database,
				std::vector<Transaction> &session_transactions){

  //init the prompts
  std::string account_name_prompt = "[withdrawal] Enter the account holder name:";
  std::string account_number_prompt = "[withdrawal] Enter the account number:";
  std::string amount_prompt = "[withdrawal] Enter amount to withdraw:";
  std::string success_prompt = "[withdrawal] Success!";
 
  std::string basic_prompt = ">> ";
  std::string account_name;
  std::string account_number;
  std::string amount;
  std::string misc = "A "; //admin - prototype only

  std::cout << account_name_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account_name; //take input from the user

  std::cout << account_number_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account_number; //take input from the user

  std::cout << amount_prompt << std::endl;
  std::cout << basic_prompt;    
  std::cin >> amount; //take input from the user

  //success message
  std::cout << success_prompt << std::endl;

  //make a new transaction
  Transaction new_transaction("withdrawal", account_name, account_number, amount, misc);
  session_transactions.push_back(new_transaction);
}





























