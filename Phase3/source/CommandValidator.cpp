#include "CommandValidator.h"

bool CommandValidator::validate(SessionStatus &current_status, std::string user_input){

  //std::cout << "USER INPUT: " + user_input << std::endl;

  if(user_input.empty())
  {
    std::cout << "End of file reached: program exitting" << std::endl;    
    exit(0);    
  }

  //If the user does not enter a valid transaction  
  if (user_input.compare("login") != 0 &&
      user_input.compare("logout") != 0 &&
      user_input.compare("withdrawal") != 0 &&
      user_input.compare("transfer") != 0 &&
      user_input.compare("paybill") != 0 &&
      user_input.compare("deposit") != 0 &&
      user_input.compare("create") != 0 &&
      user_input.compare("delete") != 0 &&
      user_input.compare("disable") != 0 &&
      user_input.compare("changeplan") != 0 &&
      user_input.compare("enable") != 0){
    std::cout << "ERROR: INVALID TRANSACTION COMMAND" << std::endl;
    return false;
  }
  
  if(!current_status.is_logged_in){
    //User is not logged in - only acceptable command is login
    if (user_input.compare("login") == 0){
      return true;
    }else{
      std::cout << "ERROR: NEED TO LOG IN FIRST" << std::endl;
      return false;
    }
  }

  //If user is already logged in
  if(user_input.compare("login") == 0){
    std::cout << "ERROR: ALREADY LOGGED IN" << std::endl;
    return false;
  }
  
  //From this point on, user has succesfully logged in
  //------------------------------------------------------
  if (current_status.is_disabled){
    //user account is disabled, only valid command is logout
    if (user_input.compare("logout") == 0){
      return true;
    }else{
      return false;
    }
  }

  //check if user is standard user
  if (!current_status.is_admin){
      if (user_input.compare("logout") == 0 ||
	  user_input.compare("withdrawal") == 0 ||
	  user_input.compare("transfer") == 0 ||
	  user_input.compare("paybill") == 0 ||
	  user_input.compare("deposit") == 0){
	return true;
      }else{
	if (user_input.compare("create") == 0 ||
	    user_input.compare("delete") == 0 ||
	    user_input.compare("disable") == 0 ||
	    user_input.compare("changeplan") == 0 ||
	    user_input.compare("enable") == 0){
	  std::cout << "ERROR: PRIVILEGED ACCESS ONLY" << std::endl;
	}
	return false;
      }
  }

  //If user is logged in as an admin
  if (current_status.is_admin){
    if (user_input.compare("logout") == 0 ||
	user_input.compare("withdrawal") == 0 ||
	user_input.compare("transfer") == 0 ||
	user_input.compare("paybill") == 0 ||
	user_input.compare("deposit") == 0 ||
	user_input.compare("create") == 0 ||
	user_input.compare("delete") == 0 ||
	user_input.compare("disable") == 0 ||
	user_input.compare("changeplan") == 0 ||
	user_input.compare("enable") == 0){
      return true;
    }else{
      return false;
    }
  }

  return false;
}

bool CommandValidator::validateAmount(std::string user_amount){
  //TODO: REGEX
  if (user_amount[5] == '.'){
    return true;
  }else{
    return false; 
  }
}

//Given an amount, verify that that amount withdrawn is a a paper current (mod 5)
bool CommandValidator::isPaperCurrency(std::string user_amount){
  float user_float = stof(user_amount);
  if (fmod(user_float,5) == 0){
    //cout << "Paper currency" << endl;
    return true;
  }else{
    //cout << "NOT Paper currency" << endl;
    return false;
  }
}






























