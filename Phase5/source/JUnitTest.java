import static org.junit.Assert.*;
import junit.framework.JUnit4TestAdapter;
import org.junit.Test;

public class JUnitTest {
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
	System.out.println("check");
	BankAccounts testBankAccounts = new BankAccounts(mbafFilename);
	Transaction testTransaction = new Transaction("00 TESTUSER1            00001 00000.00 S ");
	TransactionHandler.login(testTransaction,testBankAccounts); 
        assertEquals(false, TransactionHandler.getIsAdmin());
	TransactionHandler.logout(testTransaction,testBankAccounts); 
    }
    /*
    @Test
    public void loginTest2() {
	//check if account is a student account (ie isAdmin=true)
	BankAccounts testBankAccounts = new BankAccounts(mbafFilename);
	Transaction testTransaction = new Transaction("10 ADMIN                00000 00000.00 A ");
	TransactionHandler.login(testTransaction,testBankAccounts); 
        assertEquals(true, TransactionHandler.getIsAdmin()); //should be admin
	TransactionHandler.logout(testTransaction,testBankAccounts); 
    }
    
    @Test       
    public void logoutTest() {
	BankAccounts testBankAccounts = new BankAccounts(mbafFilename);
	Transaction testTransaction = new Transaction("10 TESTUSER1            00001 00000.00 S ");
	TransactionHandler.setIsAdmin(true); //set isAdmin to true
	TransactionHandler.logout(testTransaction,testBankAccounts); //this should change it to false
        assertEquals(false, TransactionHandler.getIsAdmin());
    }

    @Test
    public void withdrawalTest() {
	BankAccounts testBankAccounts = new BankAccounts(mbafFilename);
	Transaction testTransaction = new Transaction("10 TESTUSER1            00001 00000.00 S ");
	TransactionHandler.setIsAdmin(true); //set isAdmin to true
	TransactionHandler.logout(testTransaction,testBankAccounts); //this should change it to false
        assertEquals(false, TransactionHandler.getIsAdmin());
    }

    */
    public static junit.framework.Test suite(){
       return new JUnit4TestAdapter(JUnitTest.class);
    }
}
