#ifndef TRANSACTIONMAPPER_H_
#define TRANSACTIONMAPPER_H_

#include <map>
#include <string>

//Holds the constants for the maximum amount for transfer/paybill/withdrawal as well as the fees for student/non-student accounts
class TransactionMapper{
  
 public:
  //CONSTANTS
  //****************************TODO:this should be static, pls fix
  std::map<std::string, std::string> map_ = {
    {"logout", "00"},
    {"withdrawal", "01"},
    {"transfer", "02"},
    {"paybill", "03"},
    {"deposit", "04"},
    {"create", "05"},
    {"delete", "06"},
    {"disable", "07"},
    {"changeplan", "08"},
    {"enable", "09"},
    {"login", "10"}
  };
  
  //METHODS
  //constructor
  
  //MEMBERS
  
};

#endif






























