#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <iostream>
#include <string>

class Account{
  //CONSTANTS
  //account Number
  const int kAccNumStart = 0;
  const int kAccNumEnd = 5;

  //account holder
  const int kAccNameStart = 6;
  const int kAccNameEnd = 20;

  //account Status
  const int kAccStatusStart = 27;
  const int kAccStatusEnd = 1;

  //account balance
  const int kAccBalanceStart = 29;
  const int kAccBalanceEnd = 8;

  //account plan(student/nonstudent)
  const int kAccPlanStart = 38;
  const int kAccPlanEnd = 1;
 public:
  //Methods
  //cbaf_input_line: takes in raw input in the form NNNNN_AAAAAAAAAAAAAAAAAAAA_S_PPPPPPPP_Q
  Account(std::string cbaf_input_line);  
  void testPrint();//temp
 
  //Members
  std::string number_; //the account number
  std::string name_; //account holder name
  std::string status_; //either enabled or disabled
  float balance_; //the account balance
  std::string plan_; //Either student or non-student
  float available_balance_; //the remaining balance of the account
  float withdrawn_amount_; //cumulative amount that has been withdrawn in the current day
  float transfered_amount_; //cumulative amount that has been transfered in the current day

  //paybill amounts paid to each individual credit card company
  float cq_amount_paid_; //Cumulative amount paid to CQ 
  float ec_amount_paid_; //Cumulative amount paid to EC
  float tb_amount_paid_; //Cumulative amount paid to TB 
};

#endif


