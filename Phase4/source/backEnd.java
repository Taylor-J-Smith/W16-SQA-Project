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
	BankAccounts bankAccounts = new BankAccounts(args[0]);
	
	//read in all the transaction files
	ArrayList<Transaction> transactionsList = TransFileReader.read(args);
  
	//while transactions still esits, process them
	
	int numTransactions = transactionsList.size();
	for(int i = 0; i < numTransactions; i++){
	    Transaction currTransaction = transactionsList.get(i);
	    //TransactionHandler.handle(transactionsList.get(i), bankAccounts);
	    	//Figure out the transaction type at question
	    switch (currTransaction.transactionType) {
	    case LOGOUT: 
		TransactionHandler.logout(currTransaction, bankAccounts);
		break;
	    case WITHDRAWAL:
		TransactionHandler.withdrawal(currTransaction, bankAccounts);
		break;
	    case TRANSFER:
		Transaction nextTransaction = transactionsList.get(++i);
		TransactionHandler.transfer(currTransaction, nextTransaction, bankAccounts);
		break;
	    case PAYBILL:
		TransactionHandler.paybill(currTransaction, bankAccounts);
		break;
	    case DEPOSIT:
		TransactionHandler.deposit(currTransaction, bankAccounts);
		break;
	    case CREATE:
		TransactionHandler.create(currTransaction, bankAccounts);
		break;
	    case DELETE:
		TransactionHandler.delete(currTransaction, bankAccounts);
		break;
	    case DISABLE: 
		TransactionHandler.disable(currTransaction, bankAccounts);
		break;
	    case CHANGEPLAN: 
		TransactionHandler.changeplan(currTransaction, bankAccounts);
		break;
	    case ENABLE:
		TransactionHandler.enable(currTransaction, bankAccounts);
		break;
	    case LOGIN: 
		TransactionHandler.login(currTransaction, bankAccounts);
		break; 
	    }
	}
  
	//write the end result of all the transactions being applied to new mbaf
	String newMbafFileName = "new.mbaf";
	bankAccounts.writeToFile(newMbafFileName);
    }
}
