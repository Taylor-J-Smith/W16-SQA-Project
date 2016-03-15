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
	    secondAccount.balance_ += transferAmount - fee; 
	    firstAccount.num_trans_++; //increment the transaction number
	    secondAccount.num_trans_++; //increment the transaction number   
	}
	b.checkStatus(t1.accountNumber); //temp
	b.checkStatus(t2.accountNumber); //temp
    }

    public static void paybill(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
    }

    public static void deposit(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
    }

    public static void create(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
    }

    public static void delete(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
    }

    public static void disable(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
    }

    public static void changeplan(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
    }

    public static void enable(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
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






























