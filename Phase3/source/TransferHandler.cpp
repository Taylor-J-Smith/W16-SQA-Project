#include "TransferHandler.h"

AccountConstants TransferHandler::constants_;

void TransferHandler::handle(SessionStatus current_status, 
				AccountsDatabase &account_database,
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
    std::cout << "[transfer] ERROR: ACCOUNT HOLDER DOES NOT EXIST" << std::endl;
    return;
  }

  //Read in the amount being transfered
  std::cout << amount_prompt << std::endl;
  std::cout << basic_prompt;    
  std::cin >> amount; //take input from the user

  //verify that the user enterd a properly formated amount
  if (!CommandValidator::validateAmountFormat(amount)){
    std::cout << "[transfer] ERROR: INVALID INPUT" << std::endl;
    return;
  }else{
    //is in proper format, check if strictly > 0
    if (stof(amount) <= 0){
      std::cout << "[transfer] ERROR: INVALID INPUT" << std::endl;
      return;
    }
  }

  //Check if the user is standard and if so then check that they are under the max transfer limit
  if (!TransferHandler::isUnderTransferLimit(account_database, account1_number ,amount) &&
      !current_status.is_admin){
    std::cout << "[transfer] ERROR: AMOUNT EXCEEDS THE " << TransferHandler::constants_.kTransferMax << " LIMIT" << std::endl;
    return;
  }

  //Check to see if the transfer amount is possible given the account's balance
  if (!TransferHandler::isTransferPossible(account_database, account1_number, amount) &&
      !current_status.is_admin){
    //the transaction is not possible
    std::cout << "[transfer] ERROR: INSUFFICIENT FUNDS" << std::endl;
    return;
  }
  
  //success message
  std::cout << success_prompt << std::endl;

  //Update the accounts database to reflect the amount transfered
  TransferHandler::updateTransferedAmount(account_database, account1_number, amount);
  
  //get the second account name based on the account number given
  account2_name = account_database.getAccountName(account2_number);
  
  //TODO: update the accounts database in the frontend (not done in prototype)  
  //make a new transaction
  Transaction new_transaction1("transfer", account1_name, account1_number, amount, misc);
  Transaction new_transaction2("transfer", account2_name, account2_number, amount, misc);
  session_transactions.push_back(new_transaction1);
  session_transactions.push_back(new_transaction2);  
}

bool TransferHandler::isUnderTransferLimit(AccountsDatabase account_database,
					       std::string account_number,
					       std::string user_amount){
  Account user_account = account_database.getAccountObject(account_number);
  float user_amount_float = stof(user_amount);  
  if ((user_account.transfered_amount_ + user_amount_float) <=
      TransferHandler::constants_.kTransferMax){
    //Is under the limit
    return true;
  }else{
    //Over the permitted limit
    return false;
  }
}

//update the transfered_amount and the available_balance_ for the account with the withdrawn_instance
void TransferHandler::updateTransferedAmount(AccountsDatabase &account_database,
					     std::string account_number,
					     std::string transfer_instance){
  for(std::vector<Account>::size_type i = 0; i != account_database.database_.size(); i++){
    if (account_number.compare(account_database.database_[i].number_) == 0){
      //found the account - update the account
      account_database.database_[i].transfered_amount_ += stof(transfer_instance); //update the transfered_amount_
      account_database.database_[i].available_balance_ -= stof(transfer_instance);//update the available_balance
      return;
    }
  }
  //Did not find the account - something went wrong
  std::cout << "[TransferHandler::updateTransferedAmount] did not find account" << std::endl;
}


//Check if the amount to be transfered is possible with that account's balance
bool TransferHandler::isTransferPossible(AccountsDatabase &account_database,
					    std::string account_number,
					    std::string transfer_instance){
  for(std::vector<Account>::size_type i = 0; i != account_database.database_.size(); i++){
    if (account_number.compare(account_database.database_[i].number_) == 0){      
      //found the account - update the account
      float fee = 0.10;
      //check if it is a student account
      if (account_database.database_[i].plan_.compare("S") == 0){
	//is is a student account
	fee = 0.05;
      }

      //check if given the account balance the transfer is possible
      if ((roundf((account_database.database_[i].available_balance_ - stof(transfer_instance) - fee)*100)/100.0) < 0){
	//the user does not have the funds
	return false;
      }else{
	return true;
      }
    }
  }
  //Did not find the account - something went wrong
  std::cout << "[TransferHandler::isTransferPossible] did not find account" << std::endl;  
}
