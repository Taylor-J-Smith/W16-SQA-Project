import static org.junit.Assert.*;
import junit.framework.JUnit4TestAdapter;
import org.junit.Test;

public class JUnitTest {
    double ERROR_THRESHOLD = 1e-2;
    double STUDENT_FEE = 0.05;
    double STANDARD_FEE = 0.10;
    String mbafFilename = "old.mbaf";

    /* MBAF STATUS
       00001 TESTUSER1            A 99999.99 N 0000
       00002 TESTUSER2            A 00005.10 N 0000
       00003 TESTUSER3            A 00005.00 N 0000
       00004 TESTUSER4            D 99999.99 N 0000
       00005 TESTUSER5            A 00000.00 N 0000
       00006 TESTUSER6            A 00005.05 N 0000
       99996 TESTSTUDENT3         A 00005.00 S 0000
       99997 TESTSTUDENT2         A 00005.05 S 0000
       99998 TESTSTUDENT1         A 99999.99 S 0000
     */
    // *****************TransactionHandler.java******************
    //---------LOGIN-------
    @Test
    public void loginTest1() {
	//check if account is a non-student account (ie isAdmin=false)
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction t = new Transaction("00 TESTUSER1            00001 00000.00 S ");
	TransactionHandler.login(t,b);
        assertEquals(false, TransactionHandler.getIsAdmin());
    }

    @Test
    public void loginTest2() {
	//check if account is a student account (ie isAdmin=true)
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction t = new Transaction("10 ADMIN                00000 00000.00 A ");
	assertEquals(false, TransactionHandler.getIsAdmin()); //should not be admin
	TransactionHandler.login(t,b);
        assertEquals(true, TransactionHandler.getIsAdmin()); //should be admin
    }

    //---------LOGOUT-------
    @Test
    public void logoutTest() {
	//Check if the logout changes the isAdmin member from true to false on logout
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction t = new Transaction("10 ADMIN                00000 00000.00 A ");
	TransactionHandler.login(t,b); //Set account to admin
	assertEquals(true, TransactionHandler.getIsAdmin()); //should be admin
	TransactionHandler.logout(t,b); //this should change it to false
        assertEquals(false, TransactionHandler.getIsAdmin()); //should not be admin
    }


    //---------WITHDRAWAL-------
    @Test
    public void withdrawalTest1() {
	//ADMIN case - check if amount was removed from account
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tAdminLogin = new Transaction("10 ADMIN                00000 00000.00 A ");
	Transaction tWithdrawal = new Transaction("01 TESTUSER1            00001 00005.00   ");
	Account currAccount = b.getAccount(tWithdrawal.accountNumber);
	TransactionHandler.login(tAdminLogin,b); //Set account to admin
	assertEquals(currAccount.balance_,99999.99, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(tWithdrawal.fundsInvolved, 5.0, ERROR_THRESHOLD); //verify the withdrawal amt
	TransactionHandler.withdrawal(tWithdrawal,b);
	assertEquals(99999.99 - 5.0,
		     currAccount.balance_, ERROR_THRESHOLD); //verify the final balance
    }

    @Test
    public void withdrawalTest2() {
	//STANDARD case - check if amount was removed from account
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStdLogin = new Transaction("10 TESTUSER1            00001 00000.00 S ");
	Transaction tWithdrawal = new Transaction("01 TESTUSER1            00001 00005.00   ");
	Account currAccount = b.getAccount(tWithdrawal.accountNumber);
	TransactionHandler.login(tStdLogin,b); //Set account to admin
	assertEquals(99999.99, currAccount.balance_, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(5.0, tWithdrawal.fundsInvolved, ERROR_THRESHOLD); //verify the withdrawal amt
	TransactionHandler.withdrawal(tWithdrawal,b);
	assertEquals(99999.99 - 5.0 - STANDARD_FEE,
		     currAccount.balance_, ERROR_THRESHOLD); //verify the final balance
    }

    @Test
    public void withdrawalTest3() {
	//STUDENT case - check if amount was removed from account
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStudentLogin = new Transaction("10 TESTSTUDENT1         99998 00000.00 S ");
	Transaction tWithdrawal = new Transaction("10 TESTSTUDENT1         99998 00005.00 S ");
	Account currAccount = b.getAccount(tWithdrawal.accountNumber);
	TransactionHandler.login(tStudentLogin,b); //Set account to admin
	assertEquals(99999.99, currAccount.balance_, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(5.0, tWithdrawal.fundsInvolved, ERROR_THRESHOLD); //verify the withdrawal amt
	TransactionHandler.withdrawal(tWithdrawal,b);
	assertEquals(99999.99 - 5.0 - STUDENT_FEE,
		     currAccount.balance_, ERROR_THRESHOLD); //verify the final balance
    }

    @Test
    public void withdrawalTest4() {
	//Attempt to withdrawal more funds than possible - Expect Error
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStudentLogin = new Transaction("10 TESTSTUDENT3         99996 00000.00 S ");
	Transaction tWithdrawal = new Transaction("10 TESTSTUDENT1         99996 00005.00 S ");
	Account currAccount = b.getAccount(tWithdrawal.accountNumber);
	TransactionHandler.login(tStudentLogin,b); //Set account to admin
	assertEquals(5.0, currAccount.balance_, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(5.0, tWithdrawal.fundsInvolved, ERROR_THRESHOLD); //verify the withdrawal amt
	TransactionHandler.withdrawal(tWithdrawal,b);
	//The final balance should not have changed from original since invalid transaction
	assertEquals(5.0, currAccount.balance_, ERROR_THRESHOLD);
    }

    //----------------------TRANSFER PLACEHOLDER---------------
    @Test
    public void transferTest1() {
	//ADMIN case - check if amount was removed from account
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tAdminLogin = new Transaction("10 ADMIN                00000 00000.00 A ");
	Transaction tTransfer1 = new Transaction("02 TESTUSER1            00001 00001.00   ");
	Transaction tTransfer2 = new Transaction("02 TESTUSER2            00002 00001.00   ");
	Account currAccount1 = b.getAccount(tTransfer1.accountNumber);
	Account currAccount2 = b.getAccount(tTransfer2.accountNumber);
	TransactionHandler.login(tAdminLogin,b); //Set account to admin
	assertEquals(true, TransactionHandler.getIsAdmin()); //should be admin
	assertEquals(currAccount1.balance_,99999.99, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(currAccount2.balance_,5.10, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(tTransfer1.fundsInvolved, 1.0, ERROR_THRESHOLD); //verify the transfer amt
	TransactionHandler.transfer(tTransfer1, tTransfer2, b);
	assertEquals(99999.99 - 1.0,
		     currAccount1.balance_, ERROR_THRESHOLD); //verify the final acc1 balance
	assertEquals(5.10 + 1.0,
		     currAccount2.balance_, ERROR_THRESHOLD); //verify the final acc2 balance
    }

    @Test
    public void transferTest2() {
	//STANDARD case - check if amount was removed from account
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStdLogin = new Transaction("10 TESTUSER1            00001 00000.00 S ");
	Transaction tTransfer1 = new Transaction("02 TESTUSER1            00001 00001.00   ");
	Transaction tTransfer2 = new Transaction("02 TESTUSER2            00002 00001.00   ");
	Account currAccount1 = b.getAccount(tTransfer1.accountNumber);
	Account currAccount2 = b.getAccount(tTransfer2.accountNumber);
	TransactionHandler.login(tStdLogin,b); //Set account to admin
	assertEquals(false, TransactionHandler.getIsAdmin()); //should not be admin
	assertEquals(currAccount1.balance_,99999.99, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(currAccount2.balance_,5.10, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(tTransfer1.fundsInvolved, 1.0, ERROR_THRESHOLD); //verify the transfer amt
	TransactionHandler.transfer(tTransfer1, tTransfer2, b);
	assertEquals(99999.99 - 1.0 - STANDARD_FEE,
		     currAccount1.balance_, ERROR_THRESHOLD); //verify the final acc1 balance
	assertEquals(5.10 + 1.0 - STANDARD_FEE,
		     currAccount2.balance_, ERROR_THRESHOLD); //verify the final acc2 balance
    }

    @Test
    public void transferTest3() {
	//STUDENT case - check if amount was removed from account
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStdLogin = new Transaction("10 TESTUSER1            00001 00000.00 S ");
	Transaction tTransfer1 = new Transaction("02 TESTSTUDENT1         99998 00001.00 S ");
	Transaction tTransfer2 = new Transaction("02 TESTSTUDENT2         99997 00001.00 S ");
	Account currAccount1 = b.getAccount(tTransfer1.accountNumber);
	Account currAccount2 = b.getAccount(tTransfer2.accountNumber);
	TransactionHandler.login(tStdLogin,b); //Set account to admin
	assertEquals(false, TransactionHandler.getIsAdmin()); //should not be admin
	assertEquals(currAccount1.balance_,99999.99, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(currAccount2.balance_,5.05, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(tTransfer1.fundsInvolved, 1.0, ERROR_THRESHOLD); //verify the transfer amt
	TransactionHandler.transfer(tTransfer1, tTransfer2, b);
	assertEquals(99999.99 - 1.0 - STUDENT_FEE,
		     currAccount1.balance_, ERROR_THRESHOLD); //verify the final acc1 balance
	assertEquals(5.05 + 1.0 - STUDENT_FEE,
		     currAccount2.balance_, ERROR_THRESHOLD); //verify the final acc2 balance
    }

    @Test
    public void transferTest4() {
	//STANDARD case - Fee places first account at negative balance, expect error
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStdLogin = new Transaction("10 TESTUSER2            00002 00000.00 S ");
	Transaction tTransfer1 = new Transaction("02 TESTSTUDENT2         00002 00005.10 S ");
	Transaction tTransfer2 = new Transaction("02 TESTSTUDENT5         00005 00005.10 S ");
	Account currAccount1 = b.getAccount(tTransfer1.accountNumber);
	Account currAccount2 = b.getAccount(tTransfer2.accountNumber);
	TransactionHandler.login(tStdLogin,b); //Set account to admin
	assertEquals(false, TransactionHandler.getIsAdmin()); //should not be admin
	assertEquals(currAccount1.balance_, 5.10, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(currAccount2.balance_,0.0, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(tTransfer1.fundsInvolved, 5.10, ERROR_THRESHOLD); //verify the transfer amt
	TransactionHandler.transfer(tTransfer1, tTransfer2, b);
	assertEquals(5.10,
		     currAccount1.balance_, ERROR_THRESHOLD); //verify the final acc1 balance
	assertEquals(0.0,
		     currAccount2.balance_, ERROR_THRESHOLD); //verify the final acc2 balance
    }

    @Test
    public void transferTest5() {
	//STANDARD case - Fee places second account at negative balance, expect error
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStdLogin = new Transaction("10 TESTUSER2            00002 00000.00 S ");
	Transaction tTransfer1 = new Transaction("02 TESTSTUDENT2         00002 00000.01 S ");
	Transaction tTransfer2 = new Transaction("02 TESTSTUDENT5         00005 00000.01 S ");
	Account currAccount1 = b.getAccount(tTransfer1.accountNumber);
	Account currAccount2 = b.getAccount(tTransfer2.accountNumber);
	TransactionHandler.login(tStdLogin,b); //Set account to admin
	assertEquals(false, TransactionHandler.getIsAdmin()); //should not be admin
	assertEquals(currAccount1.balance_, 5.10, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(currAccount2.balance_,0.0, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(tTransfer1.fundsInvolved, 0.01, ERROR_THRESHOLD); //verify the transfer amt
	TransactionHandler.transfer(tTransfer1, tTransfer2, b);
	assertEquals(5.10,
		     currAccount1.balance_, ERROR_THRESHOLD); //verify the final acc1 balance
	assertEquals(0.0,
		     currAccount2.balance_, ERROR_THRESHOLD); //verify the final acc2 balance
    }

    //---------PAYBILL-------
    @Test
    public void paybillTest1() {
	//ADMIN case - check if amount was removed from account
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tAdminLogin = new Transaction("10 ADMIN                00000 00000.00 A ");
	Transaction tPaybill = new Transaction("01 TESTUSER1            00001 00005.00   ");
	Account currAccount = b.getAccount(tPaybill.accountNumber);
	TransactionHandler.login(tAdminLogin,b); //Set account to admin
	assertEquals(currAccount.balance_,99999.99, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(tPaybill.fundsInvolved, 5.0, ERROR_THRESHOLD); //verify the paybill amt
	TransactionHandler.paybill(tPaybill,b);
	assertEquals(99999.99 - 5.0,
		     currAccount.balance_, ERROR_THRESHOLD); //verify the final balance
    }

    @Test
    public void paybillTest2() {
	//STANDARD case - check if amount was removed from account
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStdLogin = new Transaction("10 TESTUSER1            00001 00000.00 S ");
	Transaction tPaybill = new Transaction("01 TESTUSER1            00001 00005.00   ");
	Account currAccount = b.getAccount(tPaybill.accountNumber);
	TransactionHandler.login(tStdLogin,b); //Set account to admin
	assertEquals(99999.99, currAccount.balance_, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(5.0, tPaybill.fundsInvolved, ERROR_THRESHOLD); //verify the paybill amt
	TransactionHandler.paybill(tPaybill,b);
	assertEquals(99999.99 - 5.0 - STANDARD_FEE,
		     currAccount.balance_, ERROR_THRESHOLD); //verify the final balance
    }

    @Test
    public void paybillTest3() {
	//STUDENT case - check if amount was removed from account
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStudentLogin = new Transaction("10 TESTSTUDENT1         99998 00000.00 S ");
	Transaction tPaybill = new Transaction("10 TESTSTUDENT1         99998 00005.00 S ");
	Account currAccount = b.getAccount(tPaybill.accountNumber);
	TransactionHandler.login(tStudentLogin,b); //Set account to admin
	assertEquals(99999.99, currAccount.balance_, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(5.0, tPaybill.fundsInvolved, ERROR_THRESHOLD); //verify the paybill amt
	TransactionHandler.paybill(tPaybill,b);
	assertEquals(99999.99 - 5.0 - STUDENT_FEE,
		     currAccount.balance_, ERROR_THRESHOLD); //verify the final balance
    }

    @Test
    public void paybillTest4() {
	//Attempt to paybill more funds than possible - Expect Error
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStudentLogin = new Transaction("10 TESTSTUDENT3         99996 00000.00 S ");
	Transaction tPaybill = new Transaction("10 TESTSTUDENT1         99996 00005.00 S ");
	Account currAccount = b.getAccount(tPaybill.accountNumber);
	TransactionHandler.login(tStudentLogin,b); //Set account to admin
	assertEquals(5.0, currAccount.balance_, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(5.0, tPaybill.fundsInvolved, ERROR_THRESHOLD); //verify the paybill amt
	TransactionHandler.paybill(tPaybill,b);
	//The final balance should not have changed from original since invalid transaction
	assertEquals(5.0, currAccount.balance_, ERROR_THRESHOLD);
    }

    //---------DEPOSIT-------
    @Test
    public void depositTest1() {
	//ADMIN case - check if amount was removed from account
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tAdminLogin = new Transaction("10 ADMIN                00000 00000.00 A ");
	Transaction tDeposit = new Transaction("01 TESTUSER1            00001 00005.00   ");
	Account currAccount = b.getAccount(tDeposit.accountNumber);
	TransactionHandler.login(tAdminLogin,b); //Set account to admin
	assertEquals(currAccount.balance_,99999.99, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(tDeposit.fundsInvolved, 5.0, ERROR_THRESHOLD); //verify the deposit amt
	TransactionHandler.deposit(tDeposit,b);
	assertEquals(99999.99 + 5.0,
		     currAccount.balance_, ERROR_THRESHOLD); //verify the final balance
    }

    @Test
    public void depositTest2() {
	//STANDARD case - check if amount was removed from account
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStdLogin = new Transaction("10 TESTUSER1            00001 00000.00 S ");
	Transaction tDeposit = new Transaction("01 TESTUSER1            00001 00005.00   ");
	Account currAccount = b.getAccount(tDeposit.accountNumber);
	TransactionHandler.login(tStdLogin,b); //Set account to admin
	assertEquals(99999.99, currAccount.balance_, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(5.0, tDeposit.fundsInvolved, ERROR_THRESHOLD); //verify the deposit amt
	TransactionHandler.deposit(tDeposit,b);
	assertEquals(99999.99 + 5.0 - STANDARD_FEE,
		     currAccount.balance_, ERROR_THRESHOLD); //verify the final balance
    }

    @Test
    public void depositTest3() {
	//STUDENT case - check if amount was removed from account
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStudentLogin = new Transaction("10 TESTSTUDENT1         99998 00000.00 S ");
	Transaction tDeposit = new Transaction("10 TESTSTUDENT1         99998 00005.00 S ");
	Account currAccount = b.getAccount(tDeposit.accountNumber);
	TransactionHandler.login(tStudentLogin,b); //Set account to admin
	assertEquals(99999.99, currAccount.balance_, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(5.0, tDeposit.fundsInvolved, ERROR_THRESHOLD); //verify the deposit amt
	TransactionHandler.deposit(tDeposit,b);
	assertEquals(99999.99 + 5.0 - STUDENT_FEE,
		     currAccount.balance_, ERROR_THRESHOLD); //verify the final balance
    }

    @Test
    public void depositTest4() {
	//Attempt to deposit more funds than possible - Expect Error
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStdLogin = new Transaction("10 TESTUSER5            00005 00000.00   ");
	Transaction tDeposit = new Transaction("01 TESTUSER5            00005 00000.01   ");
	Account currAccount = b.getAccount(tDeposit.accountNumber);
	TransactionHandler.login(tStdLogin,b); //Set account to admin
	assertEquals(0.0, currAccount.balance_, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(0.01, tDeposit.fundsInvolved, ERROR_THRESHOLD); //verify the deposit amt
	TransactionHandler.deposit(tDeposit,b);
	//The final balance should not have changed from original since invalid transaction
	assertEquals(0.0, currAccount.balance_, ERROR_THRESHOLD);
    }

    @Test
    public void createTest1(){
      BankAccounts b = new BankAccounts(mbafFilename);
      Transaction tAdminLogin = new Transaction("10 ADMIN                00000 00000.00 A ");
      Transaction tCreate = new Transaction("05 AAAAAAAAAAAAAAAAAAAA 00000 00500.00 A ");
      assertEquals(false, b.checkExists(tCreate.accountName)); //verify the account doesnt exist
      TransactionHandler.login(tAdminLogin,b); //Set account to admin
      TransactionHandler.create(tCreate,b);
      assertEquals(true, b.checkExists(tCreate.accountName)); //verify the account exists now

    }

    @Test
    public void createTest2(){
      BankAccounts b = new BankAccounts(mbafFilename);
      Transaction tAdminLogin = new Transaction("10 ADMIN                00000 00000.00 A ");
      Transaction tCreate = new Transaction("05 TESTUSER1            00000 00500.00 A ");
      assertEquals(true, b.checkExists(tCreate.accountName));
      TransactionHandler.login(tAdminLogin,b); //Set account to admin
      TransactionHandler.create(tCreate,b);
      assertEquals(true, b.checkExists(tCreate.accountName)); //verify the account still exists
      assertEquals(99999.99, b.getAccount("00001").balance_, ERROR_THRESHOLD); //verify the funds were unchanged by create

    }

    @Test
    public void deleteTest(){
      BankAccounts b = new BankAccounts(mbafFilename);
      Transaction tAdminLogin = new Transaction("10 ADMIN                00000 00000.00 A ");
      Transaction tDelete = new Transaction("05 TESTUSER1            00000 00500.00 A ");
      TransactionHandler.login(tAdminLogin,b); //Set account to admin
      assertEquals(true, b.checkExists(tDelete.accountName)); //verify the account exists
      TransactionHandler.delete(tDelete, b);
      //assertEquals(false, b.checkExists(tCreate.accountName)); //verify the account has been deleted

    }

    @Test
    public void disableTest(){
      BankAccounts b = new BankAccounts(mbafFilename);
      Transaction tAdminLogin = new Transaction("10 ADMIN                00000 00000.00 A ");
      Transaction tDisable = new Transaction("07 TESTUSER1            00001 00000.00 A ");
      TransactionHandler.login(tAdminLogin,b); //Set account to admin
      assertEquals("A", b.getAccount("00001").status_);
      TransactionHandler.disable(tDisable, b);
      assertEquals("D", b.getAccount("00001").status_);

    }

    @Test
    public void changeplanTest1(){
      BankAccounts b = new BankAccounts(mbafFilename);
      Transaction tAdminLogin = new Transaction("10 ADMIN                00000 00000.00 A ");
      Transaction tChangeplan = new Transaction("08 TESTUSER1            00001 00000.00 A ");
      TransactionHandler.login(tAdminLogin,b); //Set account to admin
      assertEquals("N", b.getAccount("00001").plan_);
      TransactionHandler.changeplan(tChangeplan, b);
      assertEquals("S", b.getAccount("00001").plan_);
    }

    @Test
    public void changeplanTest2(){
      BankAccounts b = new BankAccounts(mbafFilename);
      Transaction tAdminLogin = new Transaction("10 ADMIN                00000 00000.00 A ");
      Transaction tChangeplan = new Transaction("08 TESTSTUDENT3         00001 00000.00 A ");
      TransactionHandler.login(tAdminLogin,b); //Set account to admin
      assertEquals("N", b.getAccount("00001").plan_);
      TransactionHandler.changeplan(tChangeplan, b);
      assertEquals("S", b.getAccount("00001").plan_);
    }

    @Test
    public void enableTest(){
      BankAccounts b = new BankAccounts(mbafFilename);
      Transaction tAdminLogin = new Transaction("10 ADMIN                00000 00000.00 A ");
      Transaction tEnable = new Transaction("09 TESTUSER4            00004 00000.00 A ");
      TransactionHandler.login(tAdminLogin,b); //Set account to admin
      assertEquals("D", b.getAccount("00004").status_);
      TransactionHandler.enable(tEnable, b);
      assertEquals("A", b.getAccount("00004").status_);

    }

    @Test
    public void accountConstructorTest(){
      Account a = new Account("00001 TESTUSER1            A 99999.99 N 0000");
      assertEquals("TESTUSER1           ", a.name_);
      assertEquals("00001", a.number_);
      assertEquals("A", a.status_);
      assertEquals(99999.99, a.balance_, ERROR_THRESHOLD);
      assertEquals("N", a.plan_);
      assertEquals(0, a.num_trans_);

    }

    @Test
    public void accountToStringTest1(){
      Account a = new Account("00001 TESTUSER1            A 99999.99 N 0000");
      assertEquals("00001 TESTUSER1            A 99999.99", a.toString(false));
    }

    public static junit.framework.Test suite(){
       return new JUnit4TestAdapter(JUnitTest.class);
    }
}
