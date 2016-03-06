#include "LoginHandler.h"

void LoginHandler::handle(SessionStatus &current_status, 
				AccountsDatabase account_database,
				std::vector<Transaction> &session_transactions){
  
  //init the prompts
  std::string account_type_prompt = "[login] Enter the type of account:";
  std::string account_name_prompt = "[login] Enter the account holder name:";  
  std::string success_prompt = "[login] Success!";

  //init all the variables that will hold user input data
  std::string basic_prompt = ">> ";
  std::string account_type;
  std::string account_name;
  std::string account_number = "12345"; //temp for prototype
  std::string amount = "00000.00";
  std::string misc;

  //Read in Account Type from the user
  std::cout << account_type_prompt << std::endl;
  std::cout << basic_prompt;
  std::cin >> account_type; //take input from the user

  //Check if the account type is standard or admin
  if (account_type.compare("standard") == 0 ||
      account_type.compare("admin") == 0){
    
    //if the account is standard
    if (account_type.compare("standard") == 0){
      //standard account
      current_status.is_admin = false;
      misc = "S ";
    }else{
      //admin account
      current_status.is_admin = true;
      misc = "A "; 
    }
  }else{
    //The user did not enter the appropriate account type
    //TODO fix with more appropriate message
    std::cout << "[TEMP ERROR]: Account type can only be either admin or standard" << std::endl;
    return;
  }

  //If standard account ask for the account name
  if (!current_status.is_admin){
    //Read in the Account name from the user
    std::cout << account_name_prompt << std::endl;
    std::cout << basic_prompt;
    std::cin.ignore();
    std::getline(std::cin, account_name);
    //pad the inputted account name to 20 characters with whitespace
    while (account_name.length() < 20){
      account_name += " ";
    }
    
    //check if the account with that name exists in the database
    if(account_database.nameExists(account_name)){
      //set the account name
      current_status.account_name = account_name;
      current_status.account_number = account_database.getAccountNumber(account_name);
      current_status.is_logged_in = true;
    }else{
      std::cout << "TEMP: |" << account_name << "|" << std::endl; //temp
      std::cout << "[TEMP ERROR]: Account Name not in database" << std::endl;
      return;
    }    
  }else{
    //if admin account
    current_status.account_name = "ADMIN";
    current_status.account_number = "00000";
    current_status.is_admin = true;
    current_status.is_logged_in = true;
  }

  
  //success message - user was able to login either as admin or standard account
  std::cout << success_prompt << std::endl;
  
  //TODO: update the accounts database in the frontend (not done in prototype)
  //make a new transaction
  Transaction new_transaction("login", current_status.account_name, current_status.account_number, amount, misc);
  session_transactions.push_back(new_transaction);
}
