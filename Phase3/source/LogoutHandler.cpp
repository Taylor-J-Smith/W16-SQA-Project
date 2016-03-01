#include "LogoutHandler.h"

//Initialize the session number to 0 and the pathname to default directory
int LogoutHandler::session_number_ = 0;
std::string LogoutHandler::kPathName = "Daily-Transactions/test";

void LogoutHandler::handle(Account &current_account, 
				AccountsDatabase account_database,
				std::vector<Transaction> &session_transactions){

  std::string filename = LogoutHandler::kPathName + std::to_string(LogoutHandler::session_number_) +".tf";
  std::string success_prompt = "[logout] Success!";
  //Create the logout transaction
  Transaction new_transaction("logout", "logout_name", "12345", "00000.00", "  ");
  //push it to the session_transactions
  session_transactions.push_back(new_transaction);
  //write the transactions to a transaction file
  TransactionWriter::write(filename, session_transactions);
  //Clear the transactions of the current session
  session_transactions.clear();
  //delete the memory holding the current Account
  //delete current_account; PROTOTYPE FEATURE: MEMORY LEAK
  //clear the currentAccount
  current_account.name_ = "";
  //Increment the session number
  LogoutHandler::session_number_++;
  std::cout << success_prompt << std::endl;
}



























