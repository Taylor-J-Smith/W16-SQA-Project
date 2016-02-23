#include <stdio.h>
#include <iostream>
#include <vector>
#include <stddef.h>
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
#include "DeleteHandler.h"
#include "DisableHandler.h"
#include "EnableHandler.h"
#include "ChangeplanHandler.h"
#include "LoginHandler.h"

using namespace std;

int main(){

  //INITIALIZE
  Account *current_user = new Account();  //Declare the Current User account
  AccountsDatabase accounts_database("test.cbaf");  //create the Account Database
  vector<Transaction> session_transactions;  //Declare the vector of transactions
  TransactionMapper transaction_map;
  std::string const kWelcomePrompt = "Welcome! type login to begin:";

  //Main control loop for Front End
  while(true){
    //User has not logged in yet
    if ((*current_user).name_.compare("") == 0){
      cout << kWelcomePrompt << endl;
    }

    //Get input from user
    string user_input;
    cout << ">> ";
    cin >> user_input;

    if (!CommandValidator::validate( *current_user, user_input)){
      //user inputs an invalid command
      cout << "ERROR: INVALID COMMAND" << endl;
    }else{
      //user inputs a VALID command
      //cout << "VALID COMMAND!" << endl;
      //get the integer representation of the user transaction command
      int user_input_integer = stoi(transaction_map.map_[user_input]);
      //cout << "user_input_integer: " << user_input_integer << endl;

      switch(user_input_integer){
      case 0: //logout
	      LogoutHandler::handle(*current_user, accounts_database, session_transactions);
	      break;
      case 1: //withdrawal
	WithdrawalHandler::handle(*current_user, accounts_database, session_transactions);
	break;
      case 2: //transfer
	TransferHandler::handle(*current_user, accounts_database, session_transactions);
	break;
      case 3: //paybill
	PaybillHandler::handle(*current_user, accounts_database, session_transactions);
	break;
      case 4: //deposit
	DepositHandler::handle(*current_user, accounts_database, session_transactions);
	break;
      case 5: //create
	CreateHandler::handle(*current_user, accounts_database, session_transactions);
	break;
      case 6: //delete
	DeleteHandler::handle(*current_user, accounts_database, session_transactions);
	break;
      case 7: //disable
	DisableHandler::handle(*current_user, accounts_database, session_transactions);
	break;
      case 8: //changeplan
	ChangeplanHandler::handle(*current_user, accounts_database, session_transactions);
	break;
      case 9: //enable
	EnableHandler::handle(*current_user, accounts_database, session_transactions);
	break;
      case 10: //login
	LoginHandler::handle(*current_user, accounts_database, session_transactions);
	break;
      default:
	cout << "Case does not exist!" << endl;
	return 0;
      }
    }
  }



  //TESTCODE FOR INDIVIDUAL FUNCTIONALITY
  /*
  //  cout << "test" << endl;
  cout << "---------Account-------" << endl;
  Account *a1 = new Account("12345 TESTHOLDERNAME       A 000001.1 S");
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
  if (CommandValidator::validate(*a1,"logout")){
  cout << "Logout Validated" << endl;
  }
  //expecting a fail = no output
  if (CommandValidator::validate(*a1,"adwdw")){
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
  //CreateHandler::handle(a1, ad1, testTransVec);
  //LogoutHandler::handle(a1, ad1, testTransVec);
  cout << "--------------------------------" << endl;

  cout << "---------DeleteHandler-------" << endl;
  //DeleteHandler::handle(a1, ad1, testTransVec);
  //LogoutHandler::handle(a1, ad1, testTransVec);
  cout << "--------------------------------" << endl;

  cout << "---------DisableHandler-------" << endl;
  //DisableHandler::handle(a1, ad1, testTransVec);
  //LogoutHandler::handle(a1, ad1, testTransVec);
  cout << "--------------------------------" << endl;

  cout << "---------EnableHandler-------" << endl;
  //EnableHandler::handle(a1, ad1, testTransVec);
  //LogoutHandler::handle(a1, ad1, testTransVec);
  cout << "--------------------------------" << endl;

  cout << "---------ChangeplanHandler-------" << endl;
  //ChangeplanHandler::handle(a1, ad1, testTransVec);
  //LogoutHandler::handle(a1, ad1, testTransVec);
  cout << "--------------------------------" << endl;

  cout << "---------LoginHandler-------" << endl;
  //LoginHandler::handle(a1, ad1, testTransVec);
  //LogoutHandler::handle(a1, ad1, testTransVec);
  cout << "--------------------------------" << endl;
  */
  return 0;
}
