#ifndef DELETEHANDLER_H_
#define DELETEHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"

class DeleteHandler: public TransactionHandler{
  
 public:
  void static handle(Account current_account, 
		     AccountsDatabase account_database,
		     std::vector<Transaction> &session_transactions);
};

#endif
