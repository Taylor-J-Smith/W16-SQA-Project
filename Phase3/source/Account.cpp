#include "Account.h"

//Constructs an account with a blank name, treated as an admin [PROTOTYPE]
Account::Account(){
  this->name_ = "";
}

//Constructor for standard/regular account
//format of cbaf_input_line: 00001 TESTUSER1            A 99999.99 N
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
  this->available_balance_ = this->balance_;
  this->withdrawn_amount_ = 0.00;
  this->transfered_amount_ = 0.00;
  //Init all the XX_amount_paid_
  this->cq_amount_paid_ = 0;
  this->ec_amount_paid_ = 0;
  this->tv_amount_paid_ = 0;
  
  this->deleted_ = false;
}
