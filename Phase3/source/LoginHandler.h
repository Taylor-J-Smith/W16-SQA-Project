#ifndef LOGINHANDLER_H_
#define LOGINHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"

class LoginHandler: public TransactionHandler{
  
 public:
  //Handles the login in of a given user by verifying that the user selects a correct account type and if standard is selected they select a valid name from the database. On success, adds the transaction to the session_transactions.
  void static handle(Account &current_account, 
		     AccountsDatabase account_database,
		     std::vector<Transaction> &session_transactions);
};

#endif
