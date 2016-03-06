#include "LogoutHandler.h"

void LogoutHandler::handle(SessionStatus &current_status, 
				AccountsDatabase account_database,
				std::vector<Transaction> &session_transactions){

  std::string success_prompt = "[logout] Success!";
  //Create the logout transaction
  Transaction new_transaction("logout", current_status.account_name, current_status.account_number, "00000.00", "  ");
  //push it to the session_transactions
  session_transactions.push_back(new_transaction);
  //write the transactions to a transaction file
  TransactionWriter::write(current_status.filename, session_transactions);
  //Clear the transactions of the current session
  session_transactions.clear();

  //update the current_status and reset the account name
  current_status.is_logged_in = false;
  current_status.account_name.clear(); 
  
  //success
  std::cout << success_prompt << std::endl;  
}



























