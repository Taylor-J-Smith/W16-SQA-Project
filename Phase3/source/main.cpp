/*
******************************ALL CODE HAS BEEN PAIR PROGRAMMED******************************
*----------------------------------------Taylor Smith---------------------------------------*
*-------------------------------------Alexandar Mihaylov------------------------------------*
*-----------------------------------------Talha Zia-----------------------------------------*
*********************************************************************************************

Program Intention:
A Command Line User Interface for a Banking System that can handle different
types of transactions and account management.

Input Files: test.cbaf -> Takes a current bank accounts file that contains
the accounts used for that given day

Output Files: Daily-Transactions/test#.tf -> Contains all transactions done
in session #

How Program is Intended to run:
make -> This is a Command Line user interface where commands are entered in
the terminal and output is displayed to the terminal. The program can be
executed with the makefile provided.

[PROTOTYPE -> RELEASE] TODO:
* Check constraints in Front End
* Take an input file as a command line argument? (maybe)
* Restructure dependencies 
* Output files are not contained in source folder
* More comments?
* Fix EMACS indenting :'(

*/
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
#include "SessionStatus.h"

using namespace std;

int main(int argc, char* argv[]){
  
  //INITIALIZE
  //Obtain the command line arguments
  if (argc != 3){
    //Error not enough arguments
    cerr << "Usage: banksys <currentaccounts.txt> <transout.atf>" << endl;
    exit(0);
  }

  string input_cbaf = argv[1];
    
  //Account *current_user = new Account(); //Declare the Current User account
  SessionStatus current_status; //create a struct for the current user
  current_status.filename = argv[2]; //load the output file into the current status
  AccountsDatabase accounts_database(input_cbaf); //create the Account Database with the input cbaf
  vector<Transaction> session_transactions; //Declare the vector of transactions
  TransactionMapper transaction_map;
  string const kWelcomePrompt = "Welcome! type login to begin:";
  
  //Main control loop for Front End
  while(true){
    //User has not logged in yet
    if (!current_status.is_logged_in){
      cout << kWelcomePrompt << endl;
    }

    //Get input from user
    string user_input;
    cout << ">> ";
    cin >> user_input;

    if (!CommandValidator::validate(current_status, user_input)){
      //user inputs an invalid command
      //do nothing
    }else{
      //user inputs a VALID command
      //cout << "VALID COMMAND!" << endl;
      //get the integer representation of the user transaction command
      int user_input_integer = stoi(transaction_map.map_[user_input]);
      //cout << "user_input_integer: " << user_input_integer << endl;
      
      switch(user_input_integer){
      case 0: //logout
	LogoutHandler::handle(current_status, accounts_database, session_transactions);
	break;
      case 1: //withdrawal
	WithdrawalHandler::handle(current_status, accounts_database, session_transactions);
	break;
      case 2: //transfer
	TransferHandler::handle(current_status, accounts_database, session_transactions);
	break;
      case 3: //paybill
	PaybillHandler::handle(current_status, accounts_database, session_transactions);
	break;
      case 4: //deposit
	DepositHandler::handle(current_status, accounts_database, session_transactions);
	break;
      case 5: //create
	CreateHandler::handle(current_status, accounts_database, session_transactions);
	break;
      case 6: //delete
	DeleteHandler::handle(current_status, accounts_database, session_transactions);
	break;
      case 7: //disable
	DisableHandler::handle(current_status, accounts_database, session_transactions);
	break;
      case 8: //changeplan
	ChangeplanHandler::handle(current_status, accounts_database, session_transactions);
	break;
      case 9: //enable
	EnableHandler::handle(current_status, accounts_database, session_transactions);
	break;
      case 10: //login
	LoginHandler::handle(current_status, accounts_database, session_transactions);
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






























