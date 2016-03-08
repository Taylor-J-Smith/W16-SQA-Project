#include "WithdrawalHandler.h"

AccountConstants WithdrawalHandler::constants_;

void WithdrawalHandler::handle(SessionStatus current_status, 
				AccountsDatabase &account_database,
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

  //check if account number matches the user
  if (!account_database.isValidAccount(account_name, account_number)){
    //std::cout << current_status.account_name << ":::" << account_number << std::endl;
    std::cout << "[withdrawal] ERROR: ACCOUNT # DOES NOT MATCH HOLDER" << std::endl;
    return;
  }

  //Read in the Amount
  std::cout << amount_prompt << std::endl;
  std::cout << basic_prompt;    
  std::cin >> amount; //take input from the user
  
  //verify that the user enterd a properly formated amount
  if (!CommandValidator::validateAmountFormat(amount)){
    std::cout << "[withdrawal] ERROR: INVALID INPUT" << std::endl;
    return;
  }

  //verify that the user enterd a paper currency
  if (!WithdrawalHandler::isPaperCurrency(amount)){
    std::cout << "[withdrawal] ERROR: INVALID INPUT" << std::endl;
    return;
  }

  //Check if the user is standard and if so then check that they are under the max withdrawal limit
  if (!WithdrawalHandler::isUnderWithdrawalLimit(account_database, account_number ,amount) && !current_status.is_admin){
    std::cout << "[withdrawal] ERROR: AMOUNT EXCEEDS THE " << WithdrawalHandler::constants_.kWithdrawalMax << " LIMIT" << std::endl;
    return;
  }

  if (!account_database.isWithdrawalPossible(account_number, amount)){
    //the transaction is not possible
    std::cout << "[withdrawal] ERROR: INSUFFICIENT FUNDS" << std::endl;
    return;
  }

  //success message
  std::cout << success_prompt << std::endl;


  //Update the accounts database to reflec the amount withdrawn
  account_database.updateWithdrawnAmount(account_number, amount);
  //Account user_account = account_database.getAccountObject(account_number);
  //std::cout << account_name << user_account.withdrawn_amount_ << "+=" << stof(amount) << std::endl;
  //make a new transaction
  Transaction new_transaction("withdrawal", account_name, account_number, amount, misc);
  session_transactions.push_back(new_transaction);
}


//Given an amount, verify that that amount withdrawn is a a paper current (mod 5)
bool WithdrawalHandler::isPaperCurrency(std::string user_amount){
  float user_amount_float = stof(user_amount);
  if (fmod(user_amount_float,5) == 0){
    //cout << "Paper currency" << endl;
    return true;
  }else{
    //cout << "NOT Paper currency" << endl;
    return false;
  }
}

bool WithdrawalHandler::isUnderWithdrawalLimit(AccountsDatabase account_database,
					       std::string account_number,
					       std::string user_amount){
  Account user_account = account_database.getAccountObject(account_number);
  float user_amount_float = stof(user_amount);  
  //  if (user_amount_float <= WithdrawalHandler::constants_.kWithdrawalMax){
  if ((user_account.withdrawn_amount_ + user_amount_float) <=
      WithdrawalHandler::constants_.kWithdrawalMax){
    //Is under the limit
    return true;
  }else{
    //Over the permitted limit
    return false;
  }
}


























