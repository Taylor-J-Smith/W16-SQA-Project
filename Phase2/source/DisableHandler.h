#ifndef DISABLEHANDLER_H_
#define DISABLEHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"

class DisableHandler: public TransactionHandler{
  
 public:
  void static handle(Account current_account, 
		     AccountsDatabase account_database,
		     std::vector<Transaction> &session_transactions);
};

#endif
