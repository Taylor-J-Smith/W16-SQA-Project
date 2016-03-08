#ifndef TRANSFERHANDLER_H_
#define TRANSFERHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"
#include "SessionStatus.h"
#include "CommandValidator.h"

class TransferHandler: public TransactionHandler{

 private:
  AccountConstants static constants_;

 public:
  //Handles the transfer of money from one account to another. On success, adds two transactions to the session_transactions, one for the first account and another for the second. The account database is then updated to reflect the transaction.
  void static handle(SessionStatus current_status, 
		     AccountsDatabase &account_database,
		     std::vector<Transaction> &session_transactions);

  //Verify that the amount being transfered is <= the daily limit 1000 
  bool static isUnderTransferLimit(AccountsDatabase account_database,
				     std::string account_number,
				     std::string user_amount);
};

#endif





























