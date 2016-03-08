#ifndef PAYBILLHANDLER_H_
#define PAYBILLHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"
#include "SessionStatus.h"
#include "CommandValidator.h"

class PaybillHandler: public TransactionHandler{

 private:
  AccountConstants static constants_;

 public:
  //Handles the transaction paybill whereby money is withdrawn from the provided account and added to one of three permitted companies. The account database is then updated to reflect the transaction.
  void static handle(SessionStatus current_status, 
		     AccountsDatabase &account_database,
		     std::vector<Transaction> &session_transactions);

  //Check to see if the given company exists and is valid
  bool static isValidCompany(std::string company_ACK);

  //Verify that the amount being paid is <= the daily limit 2000 
  bool static isUnderPaybillLimit(AccountsDatabase account_database,
				  std::string account_number,
				  std::string user_amount,
				  std::string company_ACK);
  
  //Update the withdrawn amount for the given account number
  void static updatePaybillAmount(AccountsDatabase &account_database,
				  std::string account_number,
				  std::string withdrawn_instance,
				  std::string company_ACK);
  //Check if the amount to be withdrawn is possible with that account's balance
  bool static isPaybillPossible(AccountsDatabase &account_database,
				std::string account_number,
				std::string withdrawn_instance,
				std::string company_ACK);
};

#endif





























