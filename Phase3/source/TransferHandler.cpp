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
  std::string misc = "  "; //admin - prototype only

  if (current_status.is_admin){
    //Read in Account Name from the user
    std::cout << account_name_prompt << std::endl;
    std::cout << basic_prompt;
    std::cin.ignore();
    std::getline(std::cin, account1_name);
    //pad the inputted account name to 20 characters with whitespace
    while (account1_name.length() < 20){
      account1_name += " ";
    }
  }else{
    account1_name = current_status.account_name;
  }

  //Read in the first account number from user
  std::cout << account1_number_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account1_number; //take input from the user

  //check if account number matches the user
  if (!account_database.isValidAccount(account1_name, account1_number)){
    //std::cout << current_status.account_name << ":::" << account_number << std::endl;
    std::cout << "[transfer] ERROR: ACCOUNT # DOES NOT MATCH HOLDER" << std::endl;
    return;
  }

  //Read in second account number from user
  std::cout << account2_number_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account2_number; //take input from the user

  if (!account_database.numberExists(account2_number)){
    std::cout << "[transfer] ERROR: INVALID INPUT" << std::endl;
    return;
  }

  //Read in the amount being transfered
  std::cout << amount_prompt << std::endl;
  std::cout << basic_prompt;    
  std::cin >> amount; //take input from the user

  //[PROTOTYPE] TODO: only succeed on success
  //success message
  std::cout << success_prompt << std::endl;

  //get the second account name based on the account number given
  account2_name = account_database.getAccountName(account2_number);
  
  //TODO: update the accounts database in the frontend (not done in prototype)  
  //make a new transaction
  Transaction new_transaction1("transfer", account1_name, account1_number, amount, misc);
  Transaction new_transaction2("transfer", account2_name, account2_number, amount, misc);
  session_transactions.push_back(new_transaction1);
  session_transactions.push_back(new_transaction2);  
}
