#ifndef ACCOUNTCONSTANTS_H_
#define ACCOUNTCONSTANTS_H_

//Holds the constants for the maximum amount for transfer/paybill/withdrawal as well as the fees for student/non-student accounts
class AccountConstants{
  
 public:
  //CONSTANTS
  
  //student/nonstudent fees
  const float kStudentFee = 0.05;
  const float kNonStudentFee = 0.10;

  //AMOUNT LIMITS
  const float kWithdrawalMax = 500.00;
  const float kTransferMax = 1000.00;
  //paybill limits
  const float kPaybillCQMax = 2000.00;
  const float kPaybillECMax = 2000.00;
  const float kPaybillTVMax = 2000.00;
  
};

#endif






























