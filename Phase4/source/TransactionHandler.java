public class TransactionHandler{
  
  public static void handle(Transaction t, BankAccounts b){
    
    switch (Integer.parseInt(t.transactionCode)) {
      case 0:
        logout(t, b);
        break;
      case 1:
        withdrawal(t,b);
        break;            //continue on
    }
    
  }
  
  private static void logout(Transaction t, BankAccounts b){
    
  }
  
  private static void withdrawal(Transaction t, BankAccounts b){
    
  }
  
  private enum transType {LOGOUT, WITHDRAWAL, TRANSFER, PAYBILL, DEPOSIT, 
      CREATE, DELETE, DISABLE, CHANGEPLAN, ENABLE, LOGIN}
  
}
