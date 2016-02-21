#ifndef WITHDRAWALHANDLER_H_
#define WITHDRAWALHANDLER_H_

#include <string>
#include "TransactionHandler.h"
#include "AccountConstants.h"

class WithdrawalHandler: public TransactionHandler{

 private:
  //CONSTANTS
  //static std::string kAccountNamePrompt;
  //static std::string kAccountNumberPrompt;
  //static std::string kAmountPrompt;
  //static std::string kSuccessPrompt;
 
  AccountConstants constants_;

 public:
  void static handle(Account current_account, 
		     AccountsDatabase account_database,
		     std::vector<Transaction> &session_transactions);
};


#endif





























