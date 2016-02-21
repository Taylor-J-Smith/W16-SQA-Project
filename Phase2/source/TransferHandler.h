#ifndef TRANSFERHANDLER_H_
#define TRANSFERHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"

class TransferHandler: public TransactionHandler{

 private:
  AccountConstants constants_;

 public:
  void static handle(Account current_account, 
		     AccountsDatabase account_database,
		     std::vector<Transaction> &session_transactions);
};


#endif





























