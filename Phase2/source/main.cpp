#include <stdio.h>
#include <iostream>
#include "Account.h"
#include "AccountsDatabase.h"
#include "AccountConstants.h"
#include "Transaction.h"
#include "TransactionMapper.h"

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
  return 0;
}






























