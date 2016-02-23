#include "CommandValidator.h"

//just a prototype version, needs changing for actual version
bool CommandValidator::validate(Account curr_account, std::string user_input){

  //std::cout << "USER INPUT: " + user_input << std::endl;

  if(user_input.empty())
  {
    std::cout << "End of file reached: program exitting" << std::endl;
    exit(0);
  }

  if (user_input.compare("logout") == 0 ||
      user_input.compare("withdrawal") == 0 ||
      user_input.compare("transfer") == 0 ||
      user_input.compare("paybill") == 0 ||
      user_input.compare("deposit") == 0 ||
      user_input.compare("create") == 0 ||
      user_input.compare("delete") == 0 ||
      user_input.compare("disable") == 0 ||
      user_input.compare("changeplan") == 0 ||
      user_input.compare("enable") == 0 ||
      user_input.compare("login") == 0
      ){
    return true;
  }
  return false;
}
