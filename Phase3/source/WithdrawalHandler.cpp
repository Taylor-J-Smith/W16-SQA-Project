#include "WithdrawalHandler.h"

AccountConstants WithdrawalHandler::constants_;

void WithdrawalHandler::handle(SessionStatus &current_status, 
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

	if(account_database.getAccountObject(account_number).status_.compare("D") == 0){
		std::cout << "[withdrawal] ERROR: TRANSACTION NOT AVAILABLE WHILE ACCOUNT IS DISABLED" << std::endl;
		return;
	}
	
	if(account_database.getAccountObject(account_number).deleted_){
		std::cout << "[withdrawal] ERROR: ACCOUNT NOT FOUND" << std::endl;
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
  if (!WithdrawalHandler::isUnderWithdrawalLimit(account_database, account_number ,amount) &&
      !current_status.is_admin){
    std::cout << "[withdrawal] ERROR: AMOUNT EXCEEDS THE " << WithdrawalHandler::constants_.kWithdrawalMax << " LIMIT" << std::endl;
    return;
  }

  //Check to see if the withdrawal amount is possible given the account's balance
  if (!WithdrawalHandler::isWithdrawalPossible(account_database, account_number, amount) &&
      !current_status.is_admin){
    //the transaction is not possible
    std::cout << "[withdrawal] ERROR: INSUFFICIENT FUNDS" << std::endl;
    return;
  }

  //success message
  std::cout << success_prompt << std::endl;

  //Update the accounts database to reflect the amount withdrawn
  WithdrawalHandler::updateWithdrawnAmount(account_database, account_number, amount);
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

//update the withdrawn_amount and the available_balance_ for the account with the withdrawn_instance
void WithdrawalHandler::updateWithdrawnAmount(AccountsDatabase &account_database,
					     std::string account_number,
					     std::string withdrawn_instance){
  for(std::vector<Account>::size_type i = 0; i != account_database.database_.size(); i++){
    if (account_number.compare(account_database.database_[i].number_) == 0){
      //found the account - update the account
      account_database.database_[i].withdrawn_amount_ += stof(withdrawn_instance); //update the withdrawn_amount_
      account_database.database_[i].available_balance_ -= stof(withdrawn_instance);//update the available_balance
      return;
    }
  }
  //Did not find the account - something went wrong
  std::cout << "[WithdrawalHandler::updateWithdrawnAmount] did not find account" << std::endl;
}


//Check if the amount to be withdrawn is possible with that account's balance
bool WithdrawalHandler::isWithdrawalPossible(AccountsDatabase &account_database,
					    std::string account_number,
					    std::string withdrawn_instance){
  for(std::vector<Account>::size_type i = 0; i != account_database.database_.size(); i++){
    if (account_number.compare(account_database.database_[i].number_) == 0){      
      //found the account - update the account
      float fee = 0.10;
      //check if it is a student account
      if (account_database.database_[i].plan_.compare("S") == 0){
	//is is a student account
	fee = 0.05;
      }

      //check if given the account balance the withdrawal is possible
      if ((roundf((account_database.database_[i].available_balance_ - stof(withdrawn_instance) - fee)*100)/100.0) < 0){
	//the user does not have the funds
	//std::cout << "TEMP:" << database_[i].available_balance_ - stof(withdrawn_instance) - fee << std::endl;
	return false;
      }else{
	return true;
      }
    }
  }
  //Did not find the account - something went wrong
  std::cout << "[WithdrawalHandler::isWithdrawalPossible] did not find account" << std::endl;  
}
