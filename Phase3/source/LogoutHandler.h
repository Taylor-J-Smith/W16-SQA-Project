#ifndef LOGOUTHANDLER_H_
#define LOGOUTHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "TransactionWriter.h"
#include "SessionStatus.h"

class LogoutHandler: public TransactionHandler{
 public:
  //CONSTANTS
  std::string static kPathName;

  //MEMBERS
  int static session_number_;

  //METHODS
  //Adds a new logout transaction to the session_transactions and saves them to a uniquely numbered transaction file in the appropriate format. The account database is then updated to reflect the transaction.
  void static handle(SessionStatus &current_status, 
				AccountsDatabase account_database,
				  std::vector<Transaction> &session_transactions);
};

#endif






























