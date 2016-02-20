#include "Account.h"

//Constructor
Account::Account(std::string cbaf_input_line){
  //std::cout << "raw cbaf format: " +  cbaf_input_line << std::endl; //temp

  //PARSE THE RAW STRING
  //account number
  this->number_ = cbaf_input_line.substr(kAccNumStart, kAccNumEnd);
  //std::cout << "number:" + this->number_  << std::endl; //temp
  //account name
  this->name_ = cbaf_input_line.substr(kAccNameStart, kAccNameEnd);
  //std::cout << "name:" + this->name_  << std::endl; //temp
  //account status
  this->status_ = cbaf_input_line.substr(kAccStatusStart, kAccStatusEnd);
  //std::cout << "status:" + this->status_  << std::endl; //temp
  //account balance
  this->balance_ = ::atof(cbaf_input_line.substr(kAccBalanceStart, kAccBalanceEnd).c_str());
  //std::cout << "balance:" << this->balance_  << std::endl; //temp
  //account status
  this->plan_ = cbaf_input_line.substr(kAccPlanStart, kAccPlanEnd);
  //std::cout << "plan:" + this->plan_  << std::endl; //temp
}

void Account::testPrint(){
  std::cout << "testPrint:" << std::endl;
}































