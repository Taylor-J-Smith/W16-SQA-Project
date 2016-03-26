import static org.junit.Assert.*;
import java.io.*;
import junit.framework.JUnit4TestAdapter;
import org.junit.Test;
import java.util.*;

/**
 * @author      ATT 
 * @version     1.0
 * @since       2016-03-26
 */

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
    //check if account is a non-student account (ie isAdmin=false)
    public void loginTest1() {
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction t = new Transaction("00 TESTUSER1            00001 00000.00 S ");
	TransactionHandler.login(t,b);
        assertEquals(false, TransactionHandler.getIsAdmin());
    }

    @Test
    //check if account is a student account (ie isAdmin=true)
    public void loginTest2() {
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction t = new Transaction("10 ADMIN                00000 00000.00 A ");
	assertEquals(false, TransactionHandler.getIsAdmin()); //should not be admin
	TransactionHandler.login(t,b);
        assertEquals(true, TransactionHandler.getIsAdmin()); //should be admin
    }

    //---------LOGOUT-------
    @Test
    //Check if the logout changes the isAdmin member from true to false on logout
    public void logoutTest() {
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction t = new Transaction("10 ADMIN                00000 00000.00 A ");
	TransactionHandler.login(t,b); //Set account to admin
	assertEquals(true, TransactionHandler.getIsAdmin()); //should be admin
	TransactionHandler.logout(t,b); //this should change it to false
        assertEquals(false, TransactionHandler.getIsAdmin()); //should not be admin
    }


    //---------WITHDRAWAL-------
    @Test
    //ADMIN case - check if amount was removed from account
    public void withdrawalTest1() {
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
    //STANDARD case - check if amount was removed from account
    public void withdrawalTest2() {
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
    //STUDENT case - check if amount was removed from account
    public void withdrawalTest3() {
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
    //Attempt to withdrawal more funds than possible - Expect Error
    public void withdrawalTest4() {
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
    //ADMIN case - check if amount was removed from account
    public void transferTest1() {
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
    //STANDARD case - check if amount was removed from account
    public void transferTest2() {
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
    //STUDENT case - check if amount was removed from account
    public void transferTest3() {
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
    //STANDARD case - Fee places first account at negative balance, expect error
    public void transferTest4() {
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
    //STANDARD case - Fee places second account at negative balance, expect error
    public void transferTest5() {
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
    //ADMIN case - check if amount was removed from account
    public void paybillTest1() {
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
    //STANDARD case - check if amount was removed from account
    public void paybillTest2() {
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
    //STUDENT case - check if amount was removed from account
    public void paybillTest3() {
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
    //Attempt to paybill more funds than possible - Expect Error
    public void paybillTest4() {
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
    //ADMIN case - check if amount was removed from account
    public void depositTest1() {
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tAdminLogin = new Transaction("10 ADMIN                00000 00000.00 A ");
	Transaction tDeposit = new Transaction("04 TESTUSER1            00001 00005.00   ");
	Account currAccount = b.getAccount(tDeposit.accountNumber);
	TransactionHandler.login(tAdminLogin,b); //Set account to admin
	assertEquals(currAccount.balance_,99999.99, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(tDeposit.fundsInvolved, 5.0, ERROR_THRESHOLD); //verify the deposit amt
	TransactionHandler.deposit(tDeposit,b);
	assertEquals(99999.99 + 5.0,
		     currAccount.balance_, ERROR_THRESHOLD); //verify the final balance
    }

    @Test
    //STANDARD case - check if amount was removed from account
    public void depositTest2() {
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStdLogin = new Transaction("10 TESTUSER1            00001 00000.00 S ");
	Transaction tDeposit = new Transaction("04 TESTUSER1            00001 00005.00   ");
	Account currAccount = b.getAccount(tDeposit.accountNumber);
	TransactionHandler.login(tStdLogin,b); //Set account to admin
	assertEquals(99999.99, currAccount.balance_, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(5.0, tDeposit.fundsInvolved, ERROR_THRESHOLD); //verify the deposit amt
	TransactionHandler.deposit(tDeposit,b);
	assertEquals(99999.99 + 5.0 - STANDARD_FEE,
		     currAccount.balance_, ERROR_THRESHOLD); //verify the final balance
    }

    @Test
    //STUDENT case - check if amount was removed from account
    public void depositTest3() {
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStudentLogin = new Transaction("10 TESTSTUDENT1         99998 00000.00 S ");
	Transaction tDeposit = new Transaction("04 TESTSTUDENT1         99998 00005.00 S ");
	Account currAccount = b.getAccount(tDeposit.accountNumber);
	TransactionHandler.login(tStudentLogin,b); //Set account to admin
	assertEquals(99999.99, currAccount.balance_, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(5.0, tDeposit.fundsInvolved, ERROR_THRESHOLD); //verify the deposit amt
	TransactionHandler.deposit(tDeposit,b);
	assertEquals(99999.99 + 5.0 - STUDENT_FEE,
		     currAccount.balance_, ERROR_THRESHOLD); //verify the final balance
    }

    @Test
    //Attempt to deposit more funds than possible - Expect Error
    public void depositTest4() {
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tStdLogin = new Transaction("10 TESTUSER5            00005 00000.00   ");
	Transaction tDeposit = new Transaction("04 TESTUSER5            00005 00000.01   ");
	Account currAccount = b.getAccount(tDeposit.accountNumber);
	TransactionHandler.login(tStdLogin,b); //Set account to admin
	assertEquals(0.0, currAccount.balance_, ERROR_THRESHOLD); //verify the initial funds
	assertEquals(0.01, tDeposit.fundsInvolved, ERROR_THRESHOLD); //verify the deposit amt
	TransactionHandler.deposit(tDeposit,b);
	//The final balance should not have changed from original since invalid transaction
	assertEquals(0.0, currAccount.balance_, ERROR_THRESHOLD);
    }
    
    @Test
    //Check to see if the account was actually created
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
    //Check if the funds of the original account were the same
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
    //If the account is successfully removed from the bank database
    public void deleteTest(){
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tAdminLogin = new Transaction("10 ADMIN                00000 00000.00 A ");
	Transaction tDelete = new Transaction("06 TESTUSER1            00001 00000.00 A ");
	TransactionHandler.login(tAdminLogin,b); //Set account to admin
	assertEquals(true, b.checkExists(tDelete.accountName)); //verify the account exists
	TransactionHandler.delete(tDelete, b);
	assertEquals(false, b.checkExists(tDelete.accountName)); //verify the account has been deleted

    }

    @Test
    //Check if the account is disabled with the "D" flag in its status_ member
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
    //Change an account from Non-Student "N" to Student "S" with changeplan
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
    //Change an account from Student "S" to Non-Student "N" with changeplan
    public void changeplanTest2(){
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tAdminLogin = new Transaction("10 ADMIN                00000 00000.00 A ");
	Transaction tChangeplan = new Transaction("08 TESTSTUDENT3         99996 00000.00 A ");
	TransactionHandler.login(tAdminLogin,b); //Set account to admin
	assertEquals("S", b.getAccount("99996").plan_);
	TransactionHandler.changeplan(tChangeplan, b);
	assertEquals("N", b.getAccount("99996").plan_);
    }

    @Test
    //See if an already disactivated account "D" is actived "A" after calling enable
    public void enableTest(){
	BankAccounts b = new BankAccounts(mbafFilename);
	Transaction tAdminLogin = new Transaction("10 ADMIN                00000 00000.00 A ");
	Transaction tEnable = new Transaction("09 TESTUSER4            00004 00000.00 A ");
	TransactionHandler.login(tAdminLogin,b); //Set account to admin
	assertEquals("D", b.getAccount("00004").status_);
	TransactionHandler.enable(tEnable, b);
	assertEquals("A", b.getAccount("00004").status_);

    }

    // *****************Account.java******************
    
    @Test
    //Check to see if the Account Constructor class correctly parses the raw account string
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
    //If the toString() function properly outputs the account object into a string
    public void accountToStringTest1(){
	Account a = new Account("00001 TESTUSER1            A 99999.99 N 0000");
	assertEquals("00001 TESTUSER1            A 99999.99", a.toString(false));
    }

        
    // *****************Transaction.java******************
    
    @Test
    //Check to see if the constructors parses and stores the raw
    //transaction string correctly
    public void transactionConstructorTest(){
	Transaction tDeposit = new Transaction("04 TESTUSER5            00005 00000.01 A ");
	assertEquals("04", tDeposit.transactionCode);
	assertEquals("DEPOSIT", tDeposit.transactionType.toString());
	assertEquals("TESTUSER5           ", tDeposit.accountName);
	assertEquals("00005", tDeposit.accountNumber);
	assertEquals(0.01, tDeposit.fundsInvolved, ERROR_THRESHOLD);
	assertEquals("A ", tDeposit.misc);
    }

    //Test to see if the toString() function properly outputs a transaction object
    @Test    
    public void transactionToStringTest(){
	String tRawString = "04 TESTUSER5            00005 00000.01 A ";
	Transaction tDeposit = new Transaction(tRawString);
	assertEquals(tRawString, tDeposit.toString());
    }


    //*****************TransFileReader.java******************
    @Test
    //See if all the transaction files are read correctly into the inernal ArrayList
    public void transFileReaderTest(){
	//First we create a String of transaction filenames that replicates the
	//args[] used to call the back end, and then call the TransactionFileReader with them
	try{
	    String transFileDir = "trans-files/";
	    File[] files = new File(transFileDir).listFiles();
	    //Store the files into an arraylist
	    ArrayList<String> filenameArrayList = new ArrayList<String>();
	    //Add placehold in first index of arraylist since TransFileReader takes in an array
	    //with the first element being the old.mbaf file which is not relevant to this test
	    filenameArrayList.add("mbaf_placeholder");
	    //Add all the files in the given tf directory
	    for (File file: files){
		if (file.isFile() &&
		    file.getName().substring(file.getName().length() -1).compareTo("~") != 0){
		    filenameArrayList.add(transFileDir + file.getName());
		}
	    }

	    //sort the filenames in alphabetical order
	    Collections.sort(filenameArrayList);
	    
	    //Convert the arrayList into a regular array since TransFileReader Constructurs requires
	    String[] filenameArray = new String[filenameArrayList.size()];
	    filenameArray = filenameArrayList.toArray(filenameArray);
	    //filenameArray now holds the same array as args[] used to call backEnd

	    //Load the transaction files with TransactionFileReader
	    ArrayList<Transaction> transactionList = TransFileReader.read(filenameArray);
	    
	    //Now we compare the transactionList made by TransFileReader and the actual
	    //Strings that are read from each individual transaction file
	    int tActualIndex = 0;
	    
	    //Iterate through all the files in the given directory
	    for (int i = 1; i < filenameArray.length; i++){
		String transFilename = filenameArray[i];
		//System.out.println(transFilename); //temp
		//create the java boilerplate code for reading in file
		InputStream in = new FileInputStream(transFilename);
		Reader reader = new InputStreamReader(in, "UTF8");
		BufferedReader trans_file = new BufferedReader(reader);

		//holds every line that will be read in
		String curr_trans_line = trans_file.readLine();
		//Iterate over all the lines in the file
		while(curr_trans_line != null){
		    String expected = curr_trans_line;
		    String actual = transactionList.get(tActualIndex).toString();
		    // THE ACTUAL TEST -> compare the expected vs the actual
		    assertEquals(expected,actual);
		    tActualIndex++; 
		    curr_trans_line = trans_file.readLine();//read the next line
		}
		//close the file
		trans_file.close();
	    }   
	} catch (IndexOutOfBoundsException e) {
	    System.err.println("IndexOutOfBoundsException: " + e.getMessage());
	} catch (IOException e) {
	    System.err.println("Caught IOException: " + e.getMessage());
	}	
    }

    // *****************BankAccounts.java******************
    
    @Test
    //Tests to see if the mbaf file is read in and properly stores the Accounts in its internal
    //private member database of accounts
    public void bankAccountsConstructorTest(){
	String mbafFilename = "old.mbaf";
	//read in the Actual Master Bank Accounts file
	ArrayList<Account> bActual = (new BankAccounts(mbafFilename)).getBankAccountsDatabase();
	int actualIndex = 0;

	//Read in the expected bank Accounts
	try{
	    //read in the mbaf file
	    InputStream in = new FileInputStream(mbafFilename);
	    Reader reader = new InputStreamReader(in, "UTF8");
	    BufferedReader mbafFile = new BufferedReader(reader);

	    //read the file in line by line
	    String currAccLine = mbafFile.readLine();
	    while (currAccLine != null){
		//get the expected and actual accounts to Test
		String expectedAccount = new Account(currAccLine).toString(true);
		String actualAccount = bActual.get(actualIndex).toString(true);
		//System.out.println(expectedAccount + ":::::" + actualAccount);
		//The Actual Test that compares the expected vs the actual
		assertEquals(expectedAccount, actualAccount);
		
		//read in the next line
		actualIndex++;
		currAccLine = mbafFile.readLine();
	    }
	    //Catch any exceptions thrown by reading in the mbaf file
	} catch (IndexOutOfBoundsException e) {
	    System.err.println("IndexOutOfBoundsException: " + e.getMessage());
	} catch (IOException e) {
	    System.err.println("Caught IOException: " + e.getMessage());
	}
    }

    @Test
    //Case where the account exists and returns it successfully from the database
    public void getAccountTest1(){
	BankAccounts b = new BankAccounts(mbafFilename);
	Account expectedAccount = b.getBankAccountsDatabase().get(0);
	Account actualAccount = b.getAccount(expectedAccount.number_);
	//System.out.println(expectedAccount.toString(true)); //temp
	//System.out.println(actualAccount.toString(true)); //temp

	//Compare the two accounts make sure they are the same
	assertEquals(expectedAccount.number_, actualAccount.number_);
	assertEquals(expectedAccount.name_, actualAccount.name_);
	assertEquals(expectedAccount.status_, actualAccount.status_);
	assertEquals(expectedAccount.balance_, actualAccount.balance_, ERROR_THRESHOLD);
	assertEquals(expectedAccount.plan_, actualAccount.plan_);
	assertEquals(expectedAccount.num_trans_, actualAccount.num_trans_);
    }

    @Test
    //Case where the account being searched for does not exist - Expect an error
    public void getAccountTest2(){
	BankAccounts b = new BankAccounts(mbafFilename);
	Account actualAccount = b.getAccount("00000");
	//Nothing to assert, expect an error
    }

    @Test
    //Case where the account exists and returns it successfully from the database
    public void checkStatusTest1(){
	BankAccounts b = new BankAccounts(mbafFilename);
	Account expectedAccount = b.getBankAccountsDatabase().get(0);
	String expectedAccountString = expectedAccount.toString(true);
	String actualAccountString = b.checkStatus(expectedAccount.number_);

	//compare the expected vs the actual
	assertEquals(expectedAccountString, actualAccountString);
    }

    @Test
    //Case where the account being searched for does not exist - Expect an error
    public void checkStatusTest2(){
	BankAccounts b = new BankAccounts(mbafFilename);
	String expectedError = "ERROR: BankAccounts::checkStatus did not find the account!";
	String actualError = b.checkStatus("00000");

	//Compare the expected error vs the actual error
	assertEquals(expectedError, actualError);
    }

    @Test
    //Case where the account being searched for by checkExists() function actually exists
    public void checkExistsTest1(){
	BankAccounts b = new BankAccounts(mbafFilename);
	Account existingAccount = b.getBankAccountsDatabase().get(0);
	//Check if the account is actually found
	assertEquals(true, b.checkExists(existingAccount.name_));
    }

    @Test
    //Case where the account being searched for by checkExists() function does NOT exist
    public void checkExistsTest2(){
	BankAccounts b = new BankAccounts(mbafFilename);
	//Check if a non existent is being searched for that it returns false
	assertEquals(false, b.checkExists(""));
    }

    @Test
    //Case where getUniqueAccountNumber starts at 1 and finds the next available unique number
    //**Note that this case covers every statement, the error at the end should never be reached
    //but is put in place as a safety precaution that cannot be tested
    public void getUniqueAccountNumberTest1(){
	BankAccounts b = new BankAccounts(mbafFilename);
	//00001 - 00006 are all taken, so we expect that 00007 is the next available
	String expectedNumber = "00007";
	assertEquals(expectedNumber, b.getUniqueAccountNumber());
    }

    @Test
    //Check to see if an account exists = false, adds it, then check if it exists = true
    public void addAcountTest(){
	BankAccounts b = new BankAccounts(mbafFilename);
	Account a = new Account("00007 TESTUSER7            A 99999.99 N 0000");
	assertEquals(false, b.checkExists("TESTUSER7           "));
	b.addAccount(a); //adding the account to the database
	assertEquals(true, b.checkExists("TESTUSER7           "));
    }

    @Test
    //Check to see if an account that exists is successfully removed from the account database
    public void removeAccountTest1(){
	BankAccounts b = new BankAccounts(mbafFilename);
	assertEquals(true, b.checkExists("TESTUSER1           "));
	b.removeAccount("00001"); //adding the account to the database
	assertEquals(false, b.checkExists("TESTUSER1           "));
    }
    
    @Test
    //Check to see if an account that does NOT exists it simply throws an error when removing it
    public void removeAccountTest2(){
	BankAccounts b = new BankAccounts(mbafFilename);
	b.removeAccount("00007"); //adding the account to the database
	//Nothing to assert since we are expecting a printed error
    }

    @Test
    //Check to see if the mbaf (with Transaction Numbers) was written successfully
    public void writeToFileTest1() throws Exception{
	boolean withTransactionNum = true;
	
	BankAccounts b = new BankAccounts(mbafFilename);
	ArrayList<Account> bArrayList = b.getBankAccountsDatabase();
	//Write the actual mbaf file
	String actualMbafFilename = "new.mbaf";
	b.writeToFile(actualMbafFilename, withTransactionNum);

	//read in the mbaf file
	InputStream in = new FileInputStream(actualMbafFilename);
	Reader reader = new InputStreamReader(in, "UTF8");
	BufferedReader mbafFile = new BufferedReader(reader);

	//set an index to keep track of the expected Account we are on
	int expectedIndex = 0;
	//read the file in line by line	
	String actualAccountString = mbafFile.readLine();
	while (actualAccountString != null){
	    String expectedAccountString = bArrayList.get(expectedIndex).toString(withTransactionNum);
	    //System.out.println(expectedAccountString + "::::" + actualAccountString);
	    assertEquals(expectedAccountString, actualAccountString);
	    expectedIndex++; //increment the expected index
	    actualAccountString = mbafFile.readLine(); //read the next line
	}	
    }

    @Test
    //Check to see if the cbaf (WITHOUT Transaction Numbers) was written successfully
    public void writeToFileTest2() throws Exception{
	boolean withTransactionNum = false;
	
	BankAccounts b = new BankAccounts(mbafFilename);
	ArrayList<Account> bArrayList = b.getBankAccountsDatabase();
	//Write the actual mbaf file
	String actualMbafFilename = "new.cbaf";
	b.writeToFile(actualMbafFilename, withTransactionNum);

	//read in the mbaf file
	InputStream in = new FileInputStream(actualMbafFilename);
	Reader reader = new InputStreamReader(in, "UTF8");
	BufferedReader mbafFile = new BufferedReader(reader);

	//set an index to keep track of the expected Account we are on
	int expectedIndex = 0;
	//read the file in line by line	
	String actualAccountString = mbafFile.readLine();
	while (actualAccountString != null){
	    String expectedAccountString = bArrayList.get(expectedIndex).toString(withTransactionNum);
	    //System.out.println(expectedAccountString + "::::" + actualAccountString);
	    assertEquals(expectedAccountString, actualAccountString);
	    expectedIndex++; //increment the expected index
	    actualAccountString = mbafFile.readLine(); //read the next line
	}	
    }
    
    public static junit.framework.Test suite(){
	return new JUnit4TestAdapter(JUnitTest.class);
    }
}
