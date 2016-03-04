#include "DepositHandler.h"

void DepositHandler::handle(SessionStatus current_status, 
				AccountsDatabase account_database,
				std::vector<Transaction> &session_transactions){
  
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

  //Read in Account Name from the user
  std::cout << account_name_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account_name; //take input from the user

  //Read in the Account Number
  std::cout << account_number_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account_number; //take input from the user

  //Read in the Amount
  std::cout << amount_prompt << std::endl;
  std::cout << basic_prompt;    
  std::cin >> amount; //take input from the user

  //[PROTOTYPE] TODO: only succeed on success
  //success message
  std::cout << success_prompt << std::endl;

  //TODO: update the accounts database in the frontend (not done in prototype)
  //make a new transaction
  Transaction new_transaction("deposit", account_name, account_number, amount, misc);
  session_transactions.push_back(new_transaction);
}
