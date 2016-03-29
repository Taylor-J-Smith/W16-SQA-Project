import static org.junit.Assert.*;
import java.io.*;
import junit.framework.JUnit4TestAdapter;
import org.junit.Test;
import java.util.*;
import java.lang.*;

/**
 * @author      ATT
 * @version     1.0
 * @since       2016-03-26
 */

//10 ADMIN                00000 00000.00 A


//A set of JUnit Test cases for the withdrawal method with decision and loop coverage
public class JUnitDecCov{

	double ERROR_THRESHOLD = 1e-2;
    double STUDENT_FEE = 0.05;
    double STANDARD_FEE = 0.10;
    String mbafFilename = "old.mbaf";

    // Test Decision Coverage for "if(!isAdmin)"
    @Test
    public void decCov_Withdrawal1() {
    BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tAdminLogin = new Transaction("10 ADMIN                00000 00000.00 A ");
	Transaction tWithdrawal = new Transaction("01 TESTUSER1            00001 00005.00   ");
	TransactionHandler.login(tAdminLogin, b);
	assertEquals(true, TransactionHandler.getIsAdmin());

    }

    // Test Decision Coverage for "if (currAccount.plan_.compareTo("S") == 0)"
    @Test
    public void decCov_Withdrawal2() {
    BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStudentLogin = new Transaction("10 TESTSTUDENT3         99996 00000.00 S ");
	Transaction tWithdrawal = new Transaction("10 TESTSTUDENT3         99996 00000.00 S ");
	Account currAccount = b.getAccount(tStudentLogin.accountNumber);
	TransactionHandler.login(tStudentLogin, b);
	assertEquals(0, currAccount.plan_.compareTo("S"));
    }

       // Test Decision Coverage for "if (currAccount.plan_.compareTo("N") == 0)"
    @Test
    public void decCov_Withdrawal3() {
    BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStdLogin = new Transaction("10 TESTUSER1            00001 00000.00 S ");
	Transaction tWithdrawal = new Transaction("10 TESTUSER1            00001 00000.00 S ");
	Account currAccount = b.getAccount(tStdLogin.accountNumber);
	TransactionHandler.login(tStdLogin, b);
	assertEquals(0, currAccount.plan_.compareTo("N"));
    }

    @Test
    // Test Decision Coverage for "if (currAccount.balance_ - withdrawalAmount < 0)"
    public void decCov_Withdrawal4() {
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStudentLogin = new Transaction("10 TESTSTUDENT3         99996 00000.00 S ");
	Transaction tWithdrawal = new Transaction("10 TESTSTUDENT3         99996 00005.00 S ");
	Account currAccount = b.getAccount(tWithdrawal.accountNumber);
	TransactionHandler.login(tStudentLogin,b); //Set account to admin
	TransactionHandler.withdrawal(tWithdrawal,b);
	assertEquals(5.0, currAccount.balance_, ERROR_THRESHOLD);
    }

    @Test
    // Test Decision Coverage for "if (currAccount.balance_ - withdrawalAmount > 0)"
    public void decCov_Withdrawal5() {
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStudentLogin = new Transaction("10 TESTSTUDENT3         99996 00005.00 S ");
	Transaction tWithdrawal = new Transaction("10 TESTSTUDENT3         99996 00000.00 S ");
	Account currAccount = b.getAccount(tWithdrawal.accountNumber);
	TransactionHandler.login(tStudentLogin,b); //Set account to admin
	TransactionHandler.withdrawal(tWithdrawal,b);
	assertEquals(4.95, currAccount.balance_, ERROR_THRESHOLD);
    }

    @Test
    // Loop Coverage Testing for checkExists() method in the BankAccounts.java class
    // for (int i=0; i < this.bankAccounts.size(); i++)
    // for 0 times
    public void loopCov_test1() {
    	BankAccounts b = new BankAccounts("old0.mbaf");
    	assertEquals(false, b.checkExists("account"));
    }

     @Test
    // Loop Coverage Testing for checkExists() method in the BankAccounts.java class
    // for (int i=0; i < this.bankAccounts.size(); i++)
    // for 1 time
    public void loopCov_test2() {
    	BankAccounts b = new BankAccounts("old1.mbaf");
    	assertEquals(false, b.checkExists("account"));
    }

    @Test
    // Loop Coverage Testing for checkExists() method in the BankAccounts.java class
    // for (int i=0; i < this.bankAccounts.size(); i++)
    // for 2 times
    public void loopCov_test3() {
    	BankAccounts b = new BankAccounts("old2.mbaf");
    	assertEquals(false, b.checkExists("account"));
    }

    @Test
    // Loop Coverage Testing for checkExists() method in the BankAccounts.java class
    // for (int i=0; i < this.bankAccounts.size(); i++)
    // for many times
    public void loopCov_test4() {
    	BankAccounts b = new BankAccounts("old.mbaf");
    	assertEquals(false, b.checkExists("account"));
    }

    public static junit.framework.Test suite(){
	return new JUnit4TestAdapter(JUnitDecCov.class);
    }
}
