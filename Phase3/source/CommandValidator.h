#ifndef COMMANDVALIDATOR_H_
#define COMMANDVALIDATOR_H_

#include <string>
#include <iostream>
#include "SessionStatus.h"
#include <regex>
#include <math.h>

//It validates user input commands to ensure that they are in the correct format and do not break the Front End
class CommandValidator{
  
 public:
  //CONSTANTS
  
  //METHODS
  //Given an account and the user provided input by that same account, checks to see if the command is a valid command for that particular type of account  
  bool static validate(SessionStatus &current_status, std::string user_input);

  //Given an amount, verify that it meets the proper regex: \d{0,5}\.\d{2}
  bool static validateAmountFormat(std::string user_amount);

  //WITHDRAWAL SPECIFIC FUNCTIONS  
  //Given an amount, verify that that amount withdrawn is a a paper currency (mod 5) and is under the limit
  //bool static isPaperCurrency(std::string user_amount);
  //Verify that the amount being withdrawn is <= 500
  //bool static isUnderWithdrawalLimit(std::string user_amount);
  
  //MEMBERS
};

#endif




