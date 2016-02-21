#ifndef ENABLEHANDLER_H_
#define ENABLEHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"

class EnableHandler: public TransactionHandler{
  
 public:
  void static handle(Account current_account, 
		     AccountsDatabase account_database,
		     std::vector<Transaction> &session_transactions);
};

#endif
