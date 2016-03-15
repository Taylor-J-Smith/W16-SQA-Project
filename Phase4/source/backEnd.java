import java.io.*;
import java.util.ArrayList;

public class backEnd{
    public static void main(String[] args){
	//check how many arguments are given
	if (args.length < 2){
	    //invalid number of arguments
	    System.out.println("Usage: <old-mbaf> <list-of-transaction-files>");
	    System.exit(0);
	}
	//read in the Master Bank Accounts File
	BankAccounts bank_accounts = new BankAccounts(args[0]);
	
	//read in all the transaction files
	ArrayList<Transaction> transactionsList = TransFileReader.read(args);
  
  //while transactions still esits, process them
  
  //write the end result of all the transactions being applied to new mbaf
  
    }
}
