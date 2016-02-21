#ifndef CHANGEPLANHANDLER_H_
#define CHANGEPLANHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"

class ChangeplanHandler: public TransactionHandler{
  
 public:
  void static handle(Account current_account, 
		     AccountsDatabase account_database,
		     std::vector<Transaction> &session_transactions);
};

#endif
