public class TransactionHandler{

    //members
    private static boolean isAdmin = false;
    
    public static void handle(Transaction t, BankAccounts b){

	//Figure out the transaction type at question
	switch (t.transactionType) {
	case LOGOUT: 
	    logout(t, b);
	    break;
	case WITHDRAWAL:
	    withdrawal(t,b);
	    break;
	case TRANSFER:
	    transfer(t,b);
	    break;
	case PAYBILL:
	    paybill(t,b);
	    break;
	case DEPOSIT:
	    deposit(t,b);
	    break;
	case CREATE:
	    create(t,b);
	    break;
	case DELETE:
	    delete(t,b);
	    break;
	case DISABLE: 
	    disable(t,b);
	    break;
	case CHANGEPLAN: 
	    changeplan(t,b);
	    break;
	case ENABLE:
	    enable(t,b);
	    break;
	case LOGIN: 
	    login(t,b);
	    break; 
	}    
    }
  
    private static void logout(Transaction t, BankAccounts b){
	System.out.println(t.transactionType);
	//set the admin variable to false
	isAdmin = false;
    }
  
    private static void withdrawal(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
	//obtain the current account in question
	Account currAccount = b.getAccount(t.accountNumber);
	b.checkStatus(t.accountNumber); //temp
	//remove the withdrawn amount
	currAccount.balance_ -= t.fundsInvolved;
	//check if it is an admin
	if (!isAdmin){
	    //not an admin - apply fees
	    if (currAccount.plan_.compareTo("S") == 0){
		//is a student account
		currAccount.balance_ -= 0.05;
	    }else{
		//Not a student account
		currAccount.balance_ -= 0.10;
	    }
	}	
	currAccount.num_trans_++;
	b.checkStatus(t.accountNumber); //temp
    }

    private static void transfer(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
	
    }

    private static void paybill(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
    }

    private static void deposit(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
    }

    private static void create(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
    }

    private static void delete(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
    }

    private static void disable(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
    }

    private static void changeplan(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
    }

    private static void enable(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
    }
    private static void login(Transaction t, BankAccounts b){
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






























