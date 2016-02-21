#ifndef LOGOUTHANDLER_H_
#define LOGOUTHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "TransactionWriter.h"

class LogoutHandler: public TransactionHandler{
 public:
  //CONSTANTS
  std::string static kPathName;

  //MEMBERS
  int static session_number_;

  //METHODS
  void static handle(Account &current_account, 
				AccountsDatabase account_database,
				  std::vector<Transaction> &session_transactions);
};

#endif






























