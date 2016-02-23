#ifndef ACCOUNTCONSTANTS_H_
#define ACCOUNTCONSTANTS_H_

//Holds the constants for the maximum amount for transfer/paybill/withdrawal as well as the fees for student/non-student accounts
class AccountConstants{
  
 public:
  //CONSTANTS
  
  //student/nonstudent fees
  const float kStudentFee = 0.05; //fee for student accounts
  const float kNonStudentFee = 0.10; //fee for non-student accounts

  //AMOUNT LIMITS
  const float kWithdrawalMax = 500.00; //the withdrawal limit for any account
  const float kTransferMax = 1000.00; //the transfer limit for any account
  //paybill limits
  const float kPaybillCQMax = 2000.00; //the limit for CQ company
  const float kPaybillECMax = 2000.00; //the limit for EC company
  const float kPaybillTVMax = 2000.00; //the limit for TV company
  
};

#endif






























