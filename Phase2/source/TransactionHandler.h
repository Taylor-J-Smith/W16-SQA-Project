#ifndef TRANSACTIONHANDLER_H_
#define TRANSACTIONHANDLER_H_

#include <vector>
#include "Account.h"
#include "AccountsDatabase.h"
#include "Transaction.h"

class TransactionHandler{
 public:
  //methods
  void static handle(Account current_account, 
		     AccountsDatabase account_database,
		     std::vector<Transaction> &session_transactions);
};



#endif





























