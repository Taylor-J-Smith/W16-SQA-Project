public class TransactionHandler{
  
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
	//Do nothing - does not affect the MBAF
    }
  
    private static void withdrawal(Transaction t, BankAccounts b){
    	System.out.println(t.transactionType);
	
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
	//Do nothing - does not affect the MBAF
    }
}
