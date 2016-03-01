#ifndef CHANGEPLANHANDLER_H_
#define CHANGEPLANHANDLER_H_

#include <string>
#include <stdlib.h>
#include "TransactionHandler.h"
#include "AccountConstants.h"

class ChangeplanHandler: public TransactionHandler{

 public:
  //Handles the changing of plan on a given account by ensuring that the name and number provided by an admin match that of an account in the database. On success, adds the transaction to the session_transactions.
  void static handle(Account current_account,
		     AccountsDatabase account_database,
		     std::vector<Transaction> &session_transactions);
};

#endif
