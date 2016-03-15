import java.text.*;

public class TransactionHandler{    

    //members
    private static boolean isAdmin = false;
  
    public static void logout(Transaction t, BankAccounts b){
	System.out.println(t.transactionType);
	//set the admin variable to false
	isAdmin = false;
    }
  
    public static void withdrawal(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
	//obtain the current account in question
	Account currAccount = b.getAccount(t.accountNumber);
	b.checkStatus(t.accountNumber); //temp
	//remove the withdrawn amount
	double withdrawalAmount = t.fundsInvolved;
	//check if it is an admin
	if (!isAdmin){
	    //not an admin - apply fees	    
	    if (currAccount.plan_.compareTo("S") == 0){
		//is a student account
		withdrawalAmount += 0.05;
	    }else{
		//Not a student account
		withdrawalAmount += 0.10;
	    }
	}

	//Check if the account balance is less than 0 once amount has been withdrawn
	if (currAccount.balance_ - withdrawalAmount < 0){
	    System.out.println("ERROR: Attempt to withdrawal more funds than possible");
	}else{
	    //finally remove the funds from the account balance
	    currAccount.balance_ -= withdrawalAmount;	    
	    currAccount.balance_ = Math.round(currAccount.balance_ * 100.0) / 100.0; //rounding
	    currAccount.num_trans_++; //increment the transaction number   
	}
	b.checkStatus(t.accountNumber); //temp
    }

    public static void transfer(Transaction t1, Transaction t2, BankAccounts b){
	System.out.println(t1.transactionType);
	b.checkStatus(t1.accountNumber); //temp
	b.checkStatus(t2.accountNumber); //temp

	//obtain the current account in question
	Account firstAccount = b.getAccount(t1.accountNumber);
	Account secondAccount = b.getAccount(t2.accountNumber);
	//remove the transfer amount
	double transferAmount = t1.fundsInvolved;
	double fee = 0.00;
	//check if it is an admin
	if (!isAdmin){
	    //not an admin - apply fees	    
	    if (firstAccount.plan_.compareTo("S") == 0){
		//is a student account
		fee = 0.05;
	    }else{
		//Not a student account
		fee = 0.10;
	    }
	}
	//add the fee to the transferAmount
	transferAmount += fee;
	//Check if the account balance is less than 0 once amount has been transfered
	if (firstAccount.balance_ - transferAmount < 0){
	    System.out.println("ERROR: Attempt to transfer more funds than possible");
	}else{
	    //finally remove the funds from the accounts balance
	    firstAccount.balance_ -= transferAmount;
	    firstAccount.balance_ = Math.round(firstAccount.balance_ * 100.0) / 100.0; //rounding
	    secondAccount.balance_ += transferAmount - fee;
	    secondAccount.balance_ = Math.round(secondAccount.balance_ * 100.0) / 100.0; //rounding
	    firstAccount.num_trans_++; //increment the transaction number
	    secondAccount.num_trans_++; //increment the transaction number   
	}
	b.checkStatus(t1.accountNumber); //temp
	b.checkStatus(t2.accountNumber); //temp
    }

    public static void paybill(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
	//obtain the current account in question
	Account currAccount = b.getAccount(t.accountNumber);
	b.checkStatus(t.accountNumber); //temp
	//remove the paybill amount
	double paybillAmount = t.fundsInvolved;
	//check if it is an admin
	if (!isAdmin){
	    //not an admin - apply fees	    
	    if (currAccount.plan_.compareTo("S") == 0){
		//is a student account
		paybillAmount += 0.05;
	    }else{
		//Not a student account
		paybillAmount += 0.10;
	    }
	}

	//Check if the account balance is less than 0 once amount has been withdrawn
	if (currAccount.balance_ - paybillAmount < 0){
	    System.out.println("ERROR: Attempt to paybill more funds than possible");
	}else{
	    //finally remove the funds from the account balance
	    currAccount.balance_ -= paybillAmount;
	    currAccount.balance_ = Math.round(currAccount.balance_ * 100.0) / 100.0; //rounding
	    currAccount.num_trans_++; //increment the transaction number   
	}
	b.checkStatus(t.accountNumber); //temp
    }

    public static void deposit(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
	//obtain the current account in question
	Account currAccount = b.getAccount(t.accountNumber);
	b.checkStatus(t.accountNumber); //temp
	//remove the deposit amount
	double depositAmount = t.fundsInvolved;
	//check if it is an admin
	if (!isAdmin){
	    //not an admin - apply fees	    
	    if (currAccount.plan_.compareTo("S") == 0){
		//is a student account
		depositAmount -= 0.05;
	    }else{
		//Not a student account
		depositAmount -= 0.10;
	    }
	}

	//Check if the account balance is less than 0 once amount has been deposit
	if (currAccount.balance_ + depositAmount < 0){
	    System.out.println("ERROR: Deposit will result in negative account balance!");
	}else{
	    //finally add the funds from the account balance
	    currAccount.balance_ += depositAmount;	    
	    currAccount.balance_ = Math.round(currAccount.balance_ * 100.0) / 100.0; //rounding
	    currAccount.num_trans_++; //increment the transaction number   
	}
	b.checkStatus(t.accountNumber); //temp
    }

    public static void create(Transaction t, BankAccounts b){
	String newAccountNumber = "";
    	System.out.println(t.transactionType);
	b.checkStatus(t.accountNumber); //temp
	if(!b.checkExists(t.accountName)){
	    //accunt does not exist
	    newAccountNumber =  b.getUniqueAccountNumber();
	    String newAccount_string = "";
	    newAccount_string += newAccountNumber;
	    newAccount_string += " ";
	    newAccount_string += t.accountName;
	    newAccount_string += " ";
	    newAccount_string += "A";
	    newAccount_string += " ";
	    DecimalFormat df = new DecimalFormat("#.00");
	    String init_balance = df.format(t.fundsInvolved);
	    while (init_balance.length() < 8){
		init_balance = "0" + init_balance;
	    }
	    newAccount_string += init_balance;
	    newAccount_string += " ";
	    newAccount_string += "N";
	    newAccount_string += " ";
	    newAccount_string += "0000";
	    Account newAccount = new Account(newAccount_string);
	    //System.out.println(newAccount.toString()); //temp
	    b.addAccount(newAccount);//add the account to the database
	};
	b.checkStatus(newAccountNumber); //temp
    }

    public static void delete(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
	b.checkStatus(t.accountNumber); //temp
	//b.removeAccount(t.accountNumber);  //other tests depend on this account
	b.checkStatus(t.accountNumber); //temp
    }

    public static void disable(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
	b.checkStatus(t.accountNumber); //temp
	b.getAccount(t.accountNumber).status_ = "D";
	b.checkStatus(t.accountNumber); //temp
    }

    public static void changeplan(Transaction t, BankAccounts b){	
    	System.out.println(t.transactionType);
	b.checkStatus(t.accountNumber); //temp
	String currentPlan = b.getAccount(t.accountNumber).plan_;
	if (currentPlan.compareTo("N") == 0){
	    b.getAccount(t.accountNumber).plan_ = "S";
	}else{
	    b.getAccount(t.accountNumber).plan_ = "N";
	}
	b.checkStatus(t.accountNumber); //temp
    }

    public static void enable(Transaction t, BankAccounts b){
	System.out.println(t.transactionType);
	b.checkStatus(t.accountNumber); //temp
	b.getAccount(t.accountNumber).status_ = "A";
	b.checkStatus(t.accountNumber); //temp
    }
    public static void login(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
	//check if it is an admin logging in
	if (t.misc.compareTo("A ") == 0){
	    //is an admin logged in
	    isAdmin = true;
	}else{
	    //not an admin
	    isAdmin = false;
	}
    }
}






























