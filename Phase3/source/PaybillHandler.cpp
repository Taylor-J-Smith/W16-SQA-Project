#include "PaybillHandler.h"

void PaybillHandler::handle(SessionStatus current_status, 
				AccountsDatabase &account_database,
				std::vector<Transaction> &session_transactions){
  
  //init the prompts
  std::string account_name_prompt = "[paybill] Enter the account holder name:";
  std::string account_number_prompt = "[paybill] Enter the account number:";
  std::string company_prompt = "[paybill] Enter the company to pay:";
  std::string amount_prompt = "[paybill] Enter amount to pay:";
  std::string success_prompt = "[paybill] Success!";

  //init all the variables that will hold user input data
  std::string basic_prompt = ">> ";
  std::string account_name;
  std::string account_number;
  std::string company_ACK;
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

  //Read in the account number
  std::cout << account_number_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account_number; //take input from the user

  //check if account number matches the user
  if (!account_database.isValidAccount(account_name, account_number)){
    std::cout << "[paybill] ERROR: ACCOUNT # DOES NOT MATCH HOLDER" << std::endl;
    return;
  }

  //Read in the company that is being paid
  std::cout << company_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> company_ACK; //take input from the user

  //check if the the company name is valid
  if (!PaybillHandler::isValidCompany(company_ACK)){
    std::cout << "[paybill] ERROR: INVALID COMPANY" << std::endl;
    return;
  }

  //Read in the amount being paid
  std::cout << amount_prompt << std::endl;
  std::cout << basic_prompt;    
  std::cin >> amount; //take input from the user

  //verify that the user enterd a properly formated amount
  if (!CommandValidator::validateAmountFormat(amount)){
    std::cout << "[paybill] ERROR: INVALID INPUT" << std::endl;
    return;
  }

  //[PROTOTYPE] TODO: only succeed on success
  //success message
  std::cout << success_prompt << std::endl;

  //TODO: update the accounts database in the frontend (not done in prototype)
  //make a new transaction
  Transaction new_transaction("paybill", account_name, account_number, amount, company_ACK);
  session_transactions.push_back(new_transaction);
}

bool PaybillHandler::isValidCompany(std::string company_ACK){
  if (company_ACK.compare("CQ") == 0||
      company_ACK.compare("EC") == 0||
      company_ACK.compare("TV") == 0){
    //matches one of given companies
    return true;
  }else{
    return false;
  }
}
