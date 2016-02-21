#ifndef CREATEHANDLER_H_
#define CREATEHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"

class CreateHandler: public TransactionHandler{

 private:
  AccountConstants constants_;

 public:
  void static handle(Account current_account, 
		     AccountsDatabase account_database,
		     std::vector<Transaction> &session_transactions);
};

#endif
