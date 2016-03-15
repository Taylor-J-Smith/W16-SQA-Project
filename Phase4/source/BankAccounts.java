import java.io.*;
import java.util.ArrayList;

public class BankAccounts{
    private static ArrayList<Account> bank_accounts = new ArrayList<Account>();
    
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
}






























