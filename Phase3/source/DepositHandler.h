#ifndef DEPOSITHANDLER_H_
#define DEPOSITHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"

class DepositHandler: public TransactionHandler{

 private:
  AccountConstants constants_;

 public:
  //Handles the addition of money into the provided bank account. A transaction is created and added to the session_transactions on successful completion of the deposit and finally the account database is updated to reflect the deposit transaction.
  void static handle(Account current_account, 
		     AccountsDatabase account_database,
		     std::vector<Transaction> &session_transactions);
};

#endif
