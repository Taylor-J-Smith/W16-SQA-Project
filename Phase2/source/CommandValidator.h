#ifndef COMMANDVALIDATOR_H_
#define COMMANDVALIDATOR_H_

#include <string>
#include "Account.h"

//It validates user input commands to ensure that they are in the correct format and do not break the Front End
class CommandValidator{
  
 public:
  //CONSTANTS
  
  //METHODS
  bool static validate(Account curr_account, std::string user_input);
  
  //MEMBERS
};

#endif




