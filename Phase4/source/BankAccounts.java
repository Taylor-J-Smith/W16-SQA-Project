import java.io.*;
import java.util.ArrayList;

public class BankAccounts{
    private static ArrayList<Account> bank_accounts = new ArrayList<Account>();

    //constructor
    public BankAccounts(String mbaf_file_name){
	try{
	    //read in the mbaf file
	    InputStream in = new FileInputStream(mbaf_file_name);
	    Reader reader = new InputStreamReader(in, "UTF8");
	    BufferedReader mbaf_file = new BufferedReader(reader);

	    //read the file in line by line
	    String curr_account_line = mbaf_file.readLine();
	    while (curr_account_line != null){
		//System.out.println(curr_account_line); //temp
		Account new_account = new Account(curr_account_line);
		//add the new account to the list of bank_accounts
		//System.out.println(new_account.toString()); //temp debug print
		this.bank_accounts.add(new_account);		
		
		//read in the next line
		curr_account_line = mbaf_file.readLine();
	    }
	    
	} catch (IndexOutOfBoundsException e) {
	    System.err.println("IndexOutOfBoundsException: " + e.getMessage());
	} catch (IOException e) {
	    System.err.println("Caught IOException: " + e.getMessage());
	}
    }

    //Returns the account object given the account number if it is found
    public Account getAccount(String account_number){
	for (int i = 0; i < this.bank_accounts.size(); i++){
	    if (account_number.compareTo(this.bank_accounts.get(i).number_) == 0){
		//found the account
		//System.out.println("[FOUND ACCOUNT]!");
		return this.bank_accounts.get(i);
	    }
	}
	System.out.println("[BankAccounts->getAccount]ERROR: Did not find the account!");
	return null;
    }

    //for debugging purposes prints the account
    public void checkStatus(String account_number){
	for (int i = 0; i < this.bank_accounts.size(); i++){
	    if (account_number.compareTo(this.bank_accounts.get(i).number_) == 0){
		//found the account
		System.out.println(this.bank_accounts.get(i).toString());
		return;
	    }
	}
	System.out.println("[BankAccounts->checkStatus]ERROR: Did not find the account!");
    }

    //Check if a given account name exists in the account database
    public boolean checkExists(String account_name){
	for (int i = 0; i < this.bank_accounts.size(); i++){
	    if (account_name.compareTo(this.bank_accounts.get(i).name_) == 0){
		//found the account
		return true;
	    }
	}
	//System.out.println("[BankAccounts->checkExists]ERROR: Did not find the account!");
	return false;
    }

    //Find a unique account number
    public String getUniqueAccountNumber(){
	final int MAX_ACCOUNT_NUM = 99999;
	for (int uniqueNumber = 1; uniqueNumber < MAX_ACCOUNT_NUM; uniqueNumber++){
	    for (int i = 0; i < this.bank_accounts.size(); i++){
		if (Integer.parseInt(this.bank_accounts.get(i).number_) == uniqueNumber){
		    //Number exists, need to find another		    
		    break;
		}
		//Found a unique number
		if(i == this.bank_accounts.size() - 1){
		    String uniqueNumber_string = String.valueOf(uniqueNumber);
		    while(uniqueNumber_string.length() < 5){
			uniqueNumber_string = "0" + uniqueNumber_string;
		    }
		    //System.out.println("[uniqueNumber]" + uniqueNumber_string);
		    return uniqueNumber_string;
		}
	    }
	    
	}
	System.out.println("[BankAccounts->checkExists]ERROR: Did not find the account!");
	return null;
    }

    //Given an Account object adds it to the bank_accounts private ArrayList
    public void addAccount(Account newAccount){
	this.bank_accounts.add(newAccount);
    }    
}






























