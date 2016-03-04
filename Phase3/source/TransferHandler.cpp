#include "TransferHandler.h"

void TransferHandler::handle(SessionStatus current_status, 
				AccountsDatabase account_database,
				std::vector<Transaction> &session_transactions){
  
  //init the prompts
  std::string account_name_prompt = "[transfer] Enter the account holder name:";
  std::string account1_number_prompt = "[transfer] Enter the first account number:";
  std::string account2_number_prompt = "[transfer] Enter the second account number:";
  std::string amount_prompt = "[transfer] Enter amount to transfer:";
  std::string success_prompt = "[transfer] Success!";

  //init the variables that will hold user input data
  std::string basic_prompt = ">> ";
  std::string account1_name;
  std::string account2_name = "tempname";
  std::string account1_number;
  std::string account2_number;
  std::string amount;
  std::string misc = "A "; //admin - prototype only

  //Read in the Account name from the user
  std::cout << account_name_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account1_name; //take input from the user

  //Read in the first account number from user
  std::cout << account1_number_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account1_number; //take input from the user

  //Read in second account number from user
  std::cout << account2_number_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account2_number; //take input from the user

  //Read in the amount being transfered
  std::cout << amount_prompt << std::endl;
  std::cout << basic_prompt;    
  std::cin >> amount; //take input from the user

  //[PROTOTYPE] TODO: only succeed on success
  //success message
  std::cout << success_prompt << std::endl;

  
  //TODO: update the accounts database in the frontend (not done in prototype)  
  //make a new transaction
  Transaction new_transaction1("transfer", account1_name, account1_number, amount, misc);
  Transaction new_transaction2("transfer", account2_name, account2_number, amount, misc);
  session_transactions.push_back(new_transaction1);
  session_transactions.push_back(new_transaction2);  
}
