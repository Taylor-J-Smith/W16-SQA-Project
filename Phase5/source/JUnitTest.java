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

    public static junit.framework.Test suite(){
       return new JUnit4TestAdapter(JUnitTest.class);
    }
}