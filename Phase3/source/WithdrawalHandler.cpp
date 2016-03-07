#include "WithdrawalHandler.h"

void WithdrawalHandler::handle(SessionStatus current_status, 
				AccountsDatabase account_database,
				std::vector<Transaction> &session_transactions){

  //init the prompts
  std::string account_name_prompt = "[withdrawal] Enter the account holder name:";
  std::string account_number_prompt = "[withdrawal] Enter the account number:";
  std::string amount_prompt = "[withdrawal] Enter amount to withdraw:";
  std::string success_prompt = "[withdrawal] Success!";

  //init all the variables that will hold user input data
  std::string basic_prompt = ">> ";
  std::string account_name;
  std::string account_number;
  std::string amount;
  std::string misc = "  ";
  
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

  //Read in the Amount
  std::cout << amount_prompt << std::endl;
  std::cout << basic_prompt;    
  std::cin >> amount; //take input from the user

  //[PROTOTYPE] TODO: only succeed on success
  //success message
  std::cout << success_prompt << std::endl;

  //TODO: update the accounts database in the frontend (not done in prototype)
  //make a new transaction
  Transaction new_transaction("withdrawal", account_name, account_number, amount, misc);
  session_transactions.push_back(new_transaction);
}





























