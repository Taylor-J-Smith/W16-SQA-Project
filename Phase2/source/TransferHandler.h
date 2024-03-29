#ifndef TRANSFERHANDLER_H_
#define TRANSFERHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"

class TransferHandler: public TransactionHandler{

 private:
  AccountConstants constants_;

 public:
  //Handles the transfer of money from one account to another. On success, adds two transactions to the session_transactions, one for the first account and another for the second. The account database is then updated to reflect the transaction.
  void static handle(Account current_account, 
		     AccountsDatabase account_database,
		     std::vector<Transaction> &session_transactions);
};


#endif





























