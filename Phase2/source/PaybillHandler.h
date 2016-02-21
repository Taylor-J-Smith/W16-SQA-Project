#ifndef PAYBILLHANDLER_H_
#define PAYBILLHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"

class PaybillHandler: public TransactionHandler{

 private:
  AccountConstants constants_;

 public:
  void static handle(Account current_account, 
		     AccountsDatabase account_database,
		     std::vector<Transaction> &session_transactions);
};


#endif





























