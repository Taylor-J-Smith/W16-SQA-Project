#ifndef WITHDRAWALHANDLER_H_
#define WITHDRAWALHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"
#include "SessionStatus.h"
#include "CommandValidator.h"

class WithdrawalHandler: public TransactionHandler{

 private:
  //CONSTANTS
  //static std::string kAccountNamePrompt;
  //static std::string kAccountNumberPrompt;
  //static std::string kAmountPrompt;
  //static std::string kSuccessPrompt; 
  AccountConstants static constants_;

  //Given an amount, verify that that amount withdrawn is a a paper currency (mod 5) and is under the limit
  bool static isPaperCurrency(std::string user_amount);
  //Verify that the amount being withdrawn is <= 500
  bool static isUnderWithdrawalLimit(std::string user_amount);

 public:
  //Handles the removal of money from the given bank account and adds a withdrawal transaction to the session_transactions once it completes successfully. The account database is then updated to reflect the transaction.
  void static handle(SessionStatus current_status, 
		     AccountsDatabase account_database,
		     std::vector<Transaction> &session_transactions);
};


#endif





























