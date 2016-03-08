#ifndef DELETEHANDLER_H_
#define DELETEHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"
#include "SessionStatus.h"

class DeleteHandler: public TransactionHandler{
  
 public:
  //Handles the deleting of an account by ensuring that the name and number provided by an admin match that of an account in a database. On success, adds the transaction to the session_transactions.
  void static handle(SessionStatus current_status, 
		     AccountsDatabase &account_database,
		     std::vector<Transaction> &session_transactions);
         
  void static deleteAccount(AccountsDatabase &account_database,
          std::string account_number);
};

#endif
