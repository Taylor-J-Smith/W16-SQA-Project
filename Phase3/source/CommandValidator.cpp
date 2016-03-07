#include "CommandValidator.h"

//just a prototype version, needs changing for actual version
bool CommandValidator::validate(SessionStatus &current_status, std::string user_input){

  //std::cout << "USER INPUT: " + user_input << std::endl;

  if(user_input.empty())
  {
    std::cout << "End of file reached: program exitting" << std::endl;
    exit(0);
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
