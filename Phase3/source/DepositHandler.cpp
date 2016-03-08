#include "DepositHandler.h"

AccountConstants DepositHandler::constants_;

void DepositHandler::handle(SessionStatus current_status, 
				AccountsDatabase &account_database,
				std::vector<Transaction> &session_transactions){
  
  if(current_status.is_disabled){
    std::cout << "[deposit] ERROR: TRANSACTION NOT AVAILABLE WHILE ACCOUNT IS DISABLED" << std::endl;
    return;
  }
	
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
    std::cout << "[deposit] ERROR: ACCOUNT # DOES NOT MATCH HOLDER" << std::endl;
    return;
  }
  
  if(account_database.getAccountObject(account_number).status_.compare("D") == 0){
    std::cout << "[deposit] ERROR: TRANSACTION NOT AVAILABLE WHILE ACCOUNT IS DISABLED" << std::endl;
    return;
  }

  if(account_database.getAccountObject(account_number).deleted_){
    std::cout << "[deposit] ERROR: ACCOUNT NOT FOUND" << std::endl;
    return;
  }

  //Read in the Amount
  std::cout << amount_prompt << std::endl;
  std::cout << basic_prompt;    
  std::cin >> amount; //take input from the user

  //verify that the user enterd a properly formated amount
  if (!CommandValidator::validateAmountFormat(amount)){
    std::cout << "[deposit] ERROR: INVALID INPUT" << std::endl;
    return;
  }

  //Check to see if the deposit amount is possible given the account's balance
  if (!DepositHandler::isDepositPossible(account_database, account_number, amount) &&
      !current_status.is_admin){
    //the transaction is not possible
    std::cout << "[deposit] ERROR: INSUFFICIENT FUNDS" << std::endl;
    return;
  }
  
  //success message
  std::cout << success_prompt << std::endl;
  //Update the accounts database to reflect the amount withdrawn
  DepositHandler::updateDepositAmount(account_database, account_number, amount);
  //make a new transaction
  Transaction new_transaction("deposit", account_name, account_number, amount, misc);
  session_transactions.push_back(new_transaction);
}


//update the withdrawn_amount and the available_balance_ for the account with the withdrawn_instance
void DepositHandler::updateDepositAmount(AccountsDatabase &account_database,
					 std::string account_number,
					 std::string deposit_instance){
  for(std::vector<Account>::size_type i = 0; i != account_database.database_.size(); i++){
    if (account_number.compare(account_database.database_[i].number_) == 0){
      //found the account - update the account
      account_database.database_[i].deposited_amount_ += stof(deposit_instance); //update the deposit_instance
      return;
    }
  }
  //Did not find the account - something went wrong
  std::cout << "[DepositHandler::updateDepositAmount] did not find account" << std::endl;
}


//Check if the amount to be deposit is possible with that account's balance
bool DepositHandler::isDepositPossible(AccountsDatabase &account_database,
					  std::string account_number,
					  std::string deposit_instance){
  for(std::vector<Account>::size_type i = 0; i != account_database.database_.size(); i++){
    if (account_number.compare(account_database.database_[i].number_) == 0){      
      //found the account - update the account
      float fee = 0.10;
      //check if it is a student account
      if (account_database.database_[i].plan_.compare("S") == 0){
	//is is a student account
	fee = 0.05;
      }

      //check if given the account balance the deposit is possible
      if ((roundf((account_database.database_[i].available_balance_ - stof(deposit_instance) - fee)*100)/100.0) < 0 ){
	//the user does not have the funds
	return false;
	
      }else if(account_database.database_[i].available_balance_ +
	       account_database.database_[i].deposited_amount_ +
	       stof(deposit_instance) -
	       fee >= DepositHandler::constants_.kAccountBalanceMax){
	return false;
      }else{
	return true;
      }
    }
  }
  //Did not find the account - something went wrong
  std::cout << "[DepositHandler::isDepositPossible] did not find account" << std::endl;  
}
