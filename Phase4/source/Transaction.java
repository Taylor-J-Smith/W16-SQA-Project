public class Transaction{
  
    final int TRANSACTION_CODE_START = 0;
    final int TRANSACTION_CODE_END = 2;

    final int ACCOUNT_NAME_START = 3;
    final int ACCOUNT_NAME_END = 23;

    final int ACCOUNT_NUMBER_START = 24;
    final int ACCOUNT_NUMBER_END = 29;

    final int FUNDS_INVOLVED_START = 30;
    final int FUNDS_INVOLVED_END = 38;

    final int MISC_START = 39;
    final int MISC_END = 41;
  
    public Transaction(String transactionFileLine){
      
      this.transactionCode = transactionFileLine.substring(TRANSACTION_CODE_START, TRANSACTION_CODE_END);
      this.accountName = transactionFileLine.substring(ACCOUNT_NAME_START, ACCOUNT_NAME_END);
      this.accountNumber = transactionFileLine.substring(ACCOUNT_NUMBER_START, ACCOUNT_NUMBER_END);
      this.fundsInvolved = Float.parseFloat(transactionFileLine.substring(FUNDS_INVOLVED_START, FUNDS_INVOLVED_END));
      this.misc = transactionFileLine.substring(MISC_START, MISC_END);
      
    }
    
    String transactionCode;
    String accountName;
    String accountNumber;
    float fundsInvolved;
    String misc;
    
    @Override
    public String toString(){
      String returnString = "";
      
      String paddedFundsInvolved = String.valueOf(fundsInvolved);
      
      while(paddedFundsInvolved.length() < 8){
        paddedFundsInvolved = "0" + paddedFundsInvolved;
      }
      
      returnString += this.transactionCode;
      returnString += this.accountName;
      returnString += this.accountNumber;
      returnString += paddedFundsInvolved;
      returnString += this.misc;
      
      return returnString;
    }
}
