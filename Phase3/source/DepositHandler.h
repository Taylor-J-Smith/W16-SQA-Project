#ifndef DEPOSITHANDLER_H_
#define DEPOSITHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"
#include "SessionStatus.h"
#include "CommandValidator.h"

class DepositHandler: public TransactionHandler{

 private:
  AccountConstants static constants_;

 public:
  //Handles the addition of money into the provided bank account. A transaction is created and added to the session_transactions on successful completion of the deposit and finally the account database is updated to reflect the deposit transaction.
  void static handle(SessionStatus current_status, 
		     AccountsDatabase &account_database,
		     std::vector<Transaction> &session_transactions);

  
  //Update the deposit amount for the given account number
  void static updateDepositAmount(AccountsDatabase &account_database,
				  std::string account_number,
				  std::string deposit_instance);
  //Check if the amount to be deposit is possible with that account's balance
  bool static isDepositPossible(AccountsDatabase &account_database,
				std::string account_number,
				std::string deposit_instance);
};

#endif
