#ifndef SESSIONSTATUS_H_
#define SESSIONSTATUS_H_

#include <string>
//Holds information regarding the current session of the account logged in
struct SessionStatus{
  std::string filename; //the name of the transaction file to be printed at the end of the session
  int tf_number = 0; //the prefix to the filename, this will be incremented every session
  bool is_logged_in = false; //if there is a user successfully logged in
  bool is_admin = false; //if the logged in user in an admin
  bool is_disabled = false; //if the account is disabled
  std::string account_name; //the name of account currrently logged in  
};

#endif



























