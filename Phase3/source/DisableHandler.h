#ifndef DISABLEHANDLER_H_
#define DISABLEHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"
#include "SessionStatus.h"

class DisableHandler: public TransactionHandler{
  
 public:
  //Handles the disabling of an account by ensuring that the name and number provided by an admin match that of an account in the database. On success, adds the transaction to the session_transactions. 
  void static handle(SessionStatus current_status, 
		     AccountsDatabase account_database,
		     std::vector<Transaction> &session_transactions);
};

#endif
