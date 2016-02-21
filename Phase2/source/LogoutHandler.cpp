#include "LogoutHandler.h"

//Initialize the session number to 0 and the pathname to default directory
int LogoutHandler::session_number_ = 0;
std::string LogoutHandler::kPathName = "Daily-Transactions";

void TransactionHandler::handle(Account current_account, 
				AccountsDatabase account_database,
				std::vector<Transaction> &session_transactions){
  //Increment the session number
  LogoutHandler::session_number_++;
}



























