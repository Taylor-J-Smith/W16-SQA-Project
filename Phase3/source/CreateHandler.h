#ifndef CREATEHANDLER_H_
#define CREATEHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"

class CreateHandler: public TransactionHandler{
  
 public:
  //This handles the admin action of creating an account in which the admin account specifies the account holder name and initial amount of the new account. A transaction is then created and added to session_transactions.
  void static handle(Account current_account, 
		     AccountsDatabase account_database,
		     std::vector<Transaction> &session_transactions);
};

#endif
