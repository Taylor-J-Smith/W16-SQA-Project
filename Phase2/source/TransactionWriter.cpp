#include "TransactionWriter.h"

void TransactionWriter::write(std::string filename, std::vector<Transaction> session_transactions){
  std::ofstream transaction_file;
  transaction_file.open(filename);

  //iterate through the session_transactions
  for (std::vector<int>::size_type i = 0; i < session_transactions.size(); i++){
    transaction_file << session_transactions[i].to_string() + "\n";
  }
  
  transaction_file.close();  
}





























