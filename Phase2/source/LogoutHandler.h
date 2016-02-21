#ifndef LOGOUTHANDLER_H_
#define LOGOUTHANDLER_H_

#include <string>
#include "TransactionHandler.h"

class LogoutHandler: public TransactionHandler{
 public:
  //CONSTANTS
  std::string static kPathName;

  //MEMBERS
  int static session_number_;

  //METHODS
};

#endif






























