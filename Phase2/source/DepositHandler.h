#ifndef DEPOSITHANDLER_H_
#define DEPOSITHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"

class DepositHandler: public TransactionHandler{

 private:
  AccountConstants constants_;

 public:
  void static handle(Account current_account, 
		     AccountsDatabase account_database,
		     std::vector<Transaction> &session_transactions);
};

#endif
