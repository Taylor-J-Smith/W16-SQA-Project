#include "TransferHandler.h"

void TransferHandler::handle(Account current_account, 
				AccountsDatabase account_database,
				std::vector<Transaction> &session_transactions){
  
  //init the prompts
  std::string account_name_prompt = "[transfer] Enter the account holder name:";
  std::string account1_number_prompt = "[transfer] Enter the first account number:";
  std::string account2_number_prompt = "[transfer] Enter the second account number:";
  std::string amount_prompt = "[transfer] Enter amount to transfer:";
  std::string success_prompt = "[transfer] Success!";
 
  std::string basic_prompt = ">> ";
  std::string account1_name;
  std::string account2_name = "tempname";
  std::string account1_number;
  std::string account2_number;
  std::string amount;
  std::string misc = "A "; //admin - prototype only

  std::cout << account_name_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account1_name; //take input from the user

  std::cout << account1_number_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account1_number; //take input from the user

  std::cout << account2_number_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account2_number; //take input from the user

  std::cout << amount_prompt << std::endl;
  std::cout << basic_prompt;    
  std::cin >> amount; //take input from the user

  //success message
  std::cout << success_prompt << std::endl;

  
  
  //make a new transaction
  Transaction new_transaction1("transfer", account1_name, account1_number, amount, misc);
  Transaction new_transaction2("transfer", account2_name, account2_number, amount, misc);
  session_transactions.push_back(new_transaction1);
  session_transactions.push_back(new_transaction2);  
}
