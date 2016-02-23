#ifndef TRANSACTIONHANDLER_H_
#define TRANSACTIONHANDLER_H_

#include <vector>
#include "Account.h"
#include "AccountsDatabase.h"
#include "Transaction.h"

class TransactionHandler{
 public:
  //METHODS
  //A generic function that takes in an account, the current daily database, a list of the current transactions for that session, and uniquely handles them depending on the inherited version of the type of transaction. The account database is then updated to reflect the transaction.
  void static handle(Account current_account, 
		     AccountsDatabase account_database,
		     std::vector<Transaction> &session_transactions);
};



#endif





























