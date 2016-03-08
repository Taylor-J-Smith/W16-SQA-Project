#include "PaybillHandler.h"

AccountConstants PaybillHandler::constants_;

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

	if(account_database.getAccountObject(account_number).status_.compare("D") == 0){
		std::cout << "[paybill] ERROR: TRANSACTION NOT AVAILABLE WHILE ACCOUNT IS DISABLED" << std::endl;
		return;
	}
	
	if(account_database.getAccountObject(account_number).deleted_){
		std::cout << "[paybill] ERROR: ACCOUNT NOT FOUND" << std::endl;
		return;
	}
	
	if(account_database.getAccountObject(account_number).deleted_){
		std::cout << "[paybill] ERROR: ACCOUNT NOT FOUND" << std::endl;
		return;
	}

  //Read in the company that is being paid
  std::cout << company_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> company_ACK; //take input from the user

  //check if the the company name is valid
  if (!PaybillHandler::isValidCompany(company_ACK)){
    std::cout << "[paybill] ERROR: NO COMPANY FOUND WITH THAT NAME" << std::endl;
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
  
  //Check if the user is standard and if so then check that they are under the max withdrawal limit
  if (!PaybillHandler::isUnderPaybillLimit(account_database, account_number ,amount, company_ACK) &&
      !current_status.is_admin){
    std::cout << "[paybill] ERROR: AMOUNT EXCEEDS THE LIMIT" << std::endl;
    return;
  }

    //Check to see if the withdrawal amount is possible given the account's balance
  if (!PaybillHandler::isPaybillPossible(account_database, account_number, amount, company_ACK) &&
      !current_status.is_admin){
    //the transaction is not possible
    std::cout << "[paybill] ERROR: INSUFFICIENT FUNDS" << std::endl;
    return;
  }
  
  //success message
  std::cout << success_prompt << std::endl;

  //Update the accounts database to reflect the amount withdrawn
  PaybillHandler::updatePaybillAmount(account_database, account_number, amount, company_ACK);
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

//Verify that the amount being paid is <= the daily limit 2000 
bool PaybillHandler::isUnderPaybillLimit(AccountsDatabase account_database,
					       std::string account_number,
					       std::string user_amount,
					       std::string company_ACK){
  Account user_account = account_database.getAccountObject(account_number);
  float user_amount_float = stof(user_amount);
  //need to init to make compiler happy
  float company_limit = 2000.00; //the max for paybill for a given company 
  float company_amount_paid = 0; //the amount already paid towards the given company
  //[REDUNDANT-TOFIX] Find which company is being paid - //update the XX_amount_paid_	
  if (company_ACK.compare("CQ") == 0){	
    company_limit=PaybillHandler::constants_.kPaybillCQMax;
    company_amount_paid=user_account.cq_amount_paid_;
  }else if(company_ACK.compare("EC") == 0){
    company_limit=PaybillHandler::constants_.kPaybillECMax;
    company_amount_paid=user_account.ec_amount_paid_;
  }else if(company_ACK.compare("TV") == 0){
    company_limit=PaybillHandler::constants_.kPaybillTVMax;
    company_amount_paid=user_account.tv_amount_paid_;
  }else{
    //this should never reach, but just in case
    std::cout << "[PaybillHandler::isUnderPaybillLimit] Could not find company" << std::endl;
  }
  if ((company_amount_paid + user_amount_float) <= company_limit){
    //Is under the limit
    return true;
  }else{
    //Over the permitted limit
    return false;
  }
}

//update the XX_amount_paid and the available_balance_ for the account with the paybill_instance
void PaybillHandler::updatePaybillAmount(AccountsDatabase &account_database,
					 std::string account_number,
					 std::string paybill_instance,
					 std::string company_ACK){
  for(std::vector<Account>::size_type i = 0; i != account_database.database_.size(); i++){
    if (account_number.compare(account_database.database_[i].number_) == 0){
      //found the account - update the account
      //[REDUNDANT-TOFIX] Find which company is being paid - //update the XX_amount_paid_	
      if (company_ACK.compare("CQ") == 0){	
	account_database.database_[i].cq_amount_paid_ += stof(paybill_instance); 
      }else if(company_ACK.compare("EC") == 0){
	account_database.database_[i].ec_amount_paid_ += stof(paybill_instance); 
      }else if(company_ACK.compare("TV") == 0){
	account_database.database_[i].tv_amount_paid_ += stof(paybill_instance); 
      }else{
	//this should never reach, but just in case
	std::cout << "[PaybillHandler::updatePaybillAmount] Could not find company" << std::endl;
      }
      //update the available_balance
      account_database.database_[i].available_balance_ -= stof(paybill_instance);
      return;
    }
  }
  //Did not find the account - something went wrong
  std::cout << "[PaybillHandler::updatePaybillAmount] did not find account" << std::endl;
}


//Check if the amount to be paid is possible with that account's balance
bool PaybillHandler::isPaybillPossible(AccountsDatabase &account_database,
				       std::string account_number,
				       std::string paybill_instance,
				       std::string company_ACK){
  for(std::vector<Account>::size_type i = 0; i != account_database.database_.size(); i++){
    if (account_number.compare(account_database.database_[i].number_) == 0){      
      //found the account - update the account
      float fee = 0.10;
      //check if it is a student account
      if (account_database.database_[i].plan_.compare("S") == 0){
	//is is a student account
	fee = 0.05;
      }
      //check if given the account balance the paybill is possible
      if ((roundf((account_database.database_[i].available_balance_ - stof(paybill_instance) - fee)*100)/100.0) < 0){
	//the user does not have the funds
	return false;
      }else{
	return true;
      }
    }
  }
  //Did not find the account - something went wrong
  std::cout << "[PaybillHandler::isPaybillPossible] did not find account" << std::endl;  
}
