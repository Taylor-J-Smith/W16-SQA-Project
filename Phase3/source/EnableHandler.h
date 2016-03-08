#ifndef ENABLEHANDLER_H_
#define ENABLEHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"
#include "SessionStatus.h"

class EnableHandler: public TransactionHandler{
  
 public:
  //Handles the enabling of an account by ensuring that the name and number provided by an admin match that of an account in the database. On success, adds the transaction to the session_transactions.
  void static handle(SessionStatus &current_status, 
		     AccountsDatabase &account_database,
		     std::vector<Transaction> &session_transactions);

   void static enableAccount(AccountsDatabase &account_database, std::string account_number); 
};

#endif
