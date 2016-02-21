#include "PaybillHandler.h"

void PaybillHandler::handle(Account current_account, 
				AccountsDatabase account_database,
				std::vector<Transaction> &session_transactions){
  
  //init the prompts
  std::string account_name_prompt = "[paybill] Enter the account holder name:";
  std::string account_number_prompt = "[paybill] Enter the account number:";
  std::string company_prompt = "[paybill] Enter the company to pay:";
  std::string amount_prompt = "[paybill] Enter amount to pay:";
  std::string success_prompt = "[paybill] Success!";
 
  std::string basic_prompt = ">> ";
  std::string account_name;
  std::string account_number;
  std::string company_ACK;
  std::string amount;

  std::cout << account_name_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account_name; //take input from the user

  std::cout << account_number_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account_number; //take input from the user

  std::cout << company_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> company_ACK; //take input from the user

  std::cout << amount_prompt << std::endl;
  std::cout << basic_prompt;    
  std::cin >> amount; //take input from the user

  //success message
  std::cout << success_prompt << std::endl;

  //TODO: update the accounts database in the frontend (not done in prototype)
  //make a new transaction
  Transaction new_transaction("paybill", account_name, account_number, amount, company_ACK);
  session_transactions.push_back(new_transaction);
}
