#include <stdio.h>
#include <iostream>
#include <vector>
#include "Account.h"
#include "AccountsDatabase.h"
#include "AccountConstants.h"
#include "Transaction.h"
#include "TransactionMapper.h"
#include "TransactionWriter.h"
#include "CommandValidator.h"
#include "TransactionHandler.h"
#include "LogoutHandler.h"
#include "WithdrawalHandler.h"
#include "TransferHandler.h"
#include "PaybillHandler.h"
#include "DepositHandler.h"
#include "CreateHandler.h"

using namespace std;

int main(){
  //  cout << "test" << endl;
  cout << "---------Account-------" << endl;
  Account a1("12345 TESTHOLDERNAME       A 000001.1 S");
  cout << "-----------------------" << endl;

  cout << "---------AccountsDatabase-------" << endl;
  AccountsDatabase ad1("test.cbaf");
  if (ad1.nameExists("test1") && ad1.isValidAccount("test1", "12345")){
    cout << "found test name and number in database" << endl;
  }
  cout << "--------------------------------" << endl;

  cout << "---------AccountConstants-------" << endl;
  AccountConstants ac1;
  cout << "Some constants:" << endl;
  cout << ac1.kStudentFee << endl;
  cout << ac1.kNonStudentFee << endl;  
  cout << "--------------------------------" << endl;

  cout << "---------TransactionMapper-------" << endl;
  TransactionMapper tm1;  
  cout << "Transaction names/codes:" << endl;
  cout << tm1.map_["logout"] << endl;
  cout << tm1.map_["login"] << endl;
  //cout << TransactionMapper::map_["logout"] << endl;
  cout << "--------------------------------" << endl;

  cout << "---------Transaction-------" << endl;
  Transaction t1("login", "test_name", "01234", "5.00", "no");
  Transaction t2("login", "test_name2", "54321", "10.00", "no");  
  cout << t1.to_string() << endl;
  //cout << TransactionMapper::map_["logout"] << endl;
  cout << "--------------------------------" << endl;

  cout << "---------TransactionWriter-------" << endl;
  vector<Transaction> testTransVec;
  testTransVec.push_back(t1);
  testTransVec.push_back(t2);
  cout << "wrote to test1.trans temporary file" << endl;
  TransactionWriter::write("test1.trans", testTransVec);
  cout << "--------------------------------" << endl;

  cout << "---------CommandValidator-------" << endl;
  if (CommandValidator::validate(a1,"logout")){
    cout << "Logout Validated" << endl;
  }
  //expecting a fail = no output
  if (CommandValidator::validate(a1,"adwdw")){
    cout << "Gibberish Validated" << endl;
  }
  cout << "--------------------------------" << endl;

  cout << "---------LogoutHandler-------" << endl;
  LogoutHandler::handle(a1, ad1, testTransVec);  
  cout << LogoutHandler::session_number_ << endl;
  LogoutHandler::handle(a1, ad1, testTransVec);  
  cout << LogoutHandler::session_number_ << endl;
  cout << "--------------------------------" << endl;

  cout << "---------WithdrawalHandler-------" << endl;
  //WithdrawalHandler::handle(a1, ad1, testTransVec);
  //LogoutHandler::handle(a1, ad1, testTransVec);
  cout << "--------------------------------" << endl;

  cout << "---------TransferHandler-------" << endl;
  //TransferHandler::handle(a1, ad1, testTransVec);
  //LogoutHandler::handle(a1, ad1, testTransVec);
  cout << "--------------------------------" << endl;

  cout << "---------PaybillHandler-------" << endl;
  //PaybillHandler::handle(a1, ad1, testTransVec);
  //LogoutHandler::handle(a1, ad1, testTransVec);
  cout << "--------------------------------" << endl;

  cout << "---------DepositHandler-------" << endl;
  //DepositHandler::handle(a1, ad1, testTransVec);
  //LogoutHandler::handle(a1, ad1, testTransVec);
  cout << "--------------------------------" << endl;

  cout << "---------CreateHandler-------" << endl;
  CreateHandler::handle(a1, ad1, testTransVec);
  LogoutHandler::handle(a1, ad1, testTransVec);
  cout << "--------------------------------" << endl;  
  return 0;
}






























