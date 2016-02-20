#ifndef TRANSACTIONWRITER_H_
#define TRANSACTIONWRITER_H_

#include <string>
#include <vector>
#include <fstream>
#include "Transaction.h"

//Holds the constants for the maximum amount for transfer/paybill/withdrawal as well as the fees for student/non-student accounts
class TransactionWriter{
  
 public:
  //CONSTANTS
  
  //METHODS
  //constructor
  
  //MEMBERS
  void static write(std::string filename, std::vector<Transaction> session_transactions);
};

#endif






























