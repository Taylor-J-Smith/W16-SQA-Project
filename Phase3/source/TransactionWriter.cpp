#include "TransactionWriter.h"

void TransactionWriter::write(std::string filename, std::vector<Transaction> session_transactions){
  std::ofstream transaction_file;
  //open the transaction file for writing
  transaction_file.open(filename,std::ios_base::app);
  //iterate through all the transactions for the given session and append them a file, each on a new line
  for (std::vector<int>::size_type i = 0; i < session_transactions.size(); i++){
    //add the current transaction to the file with a newline
    transaction_file << session_transactions[i].to_string() + "\n";
  }
  //close the transaction file
  transaction_file.close();  
}





























