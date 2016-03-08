#ifndef PAYBILLHANDLER_H_
#define PAYBILLHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"
#include "SessionStatus.h"
#include "CommandValidator.h"

class PaybillHandler: public TransactionHandler{

 private:
  AccountConstants constants_;

 public:
  //Handles the transaction paybill whereby money is withdrawn from the provided account and added to one of three permitted companies. The account database is then updated to reflect the transaction.
  void static handle(SessionStatus current_status, 
		     AccountsDatabase &account_database,
		     std::vector<Transaction> &session_transactions);

  bool static isValidCompany(std::string company_ACK);
};

#endif





























