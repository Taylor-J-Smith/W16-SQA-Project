#ifndef PAYBILLHANDLER_H_
#define PAYBILLHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"

class PaybillHandler: public TransactionHandler{

 private:
  AccountConstants constants_;

 public:
  //Handles the transaction paybill whereby money is withdrawn from the provided account and added to one of three permitted companies. The account database is then updated to reflect the transaction.
  void static handle(Account current_account, 
		     AccountsDatabase account_database,
		     std::vector<Transaction> &session_transactions);
};

#endif





























