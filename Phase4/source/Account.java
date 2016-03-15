public class Account{
    //CONSTANTS
    //account Number
    private final int kAccNumStart = 0;
    private final int kAccNumEnd = 5;

    //account holder
    private final int kAccNameStart = 6;
    private final int kAccNameEnd = 26;

    //account Status
    private final int kAccStatusStart = 27;
    private final int kAccStatusEnd = 28;

    //account balance
    private final int kAccBalanceStart = 29;
    private final int kAccBalanceEnd = 37;

    //account plan(student/nonstudent)
    private final int kAccPlanStart = 38;
    private final int kAccPlanEnd = 39;

    //number of transactions for an account
    private final int kAccTransNumStart = 40;
    private final int kAccTransNumEnd = 44;
    
    //Members
    String number_;
    String name_;
    String status_;
    double balance_;
    String plan_;
    int num_trans_;
    
    //Constructor
    public Account (String mbaf_input_line){
	//Parse the raw master bank account file line into the respective members
	this.number_ = mbaf_input_line.substring(kAccNumStart, kAccNumEnd);
	this.name_ = mbaf_input_line.substring(kAccNameStart, kAccNameEnd);
	this.status_ = mbaf_input_line.substring(kAccStatusStart, kAccStatusEnd);
	this.balance_ = Double.parseDouble(mbaf_input_line.substring(kAccBalanceStart,
								   kAccBalanceEnd));
	this.plan_ = mbaf_input_line.substring(kAccPlanStart, kAccPlanEnd);
	this.num_trans_ = Integer.parseInt(mbaf_input_line.substring(kAccTransNumStart,
								     kAccTransNumEnd));
    }

    @Override
    //Override the toString method for an account
    public String toString(){
	String returnString = "";
	    returnString += this.number_ + " ";
	    returnString += this.name_ + " ";
	    returnString += this.status_ + " ";
	    //need to pad the balance to 8 characters
	    String balance_string = String.valueOf(this.balance_);
	    while(balance_string.length() < 8){
		balance_string = "0" + balance_string;
	    }
	    returnString += balance_string + " ";
	    returnString += this.plan_ + " ";
	    String num_trans_string = String.valueOf(this.num_trans_);
	    while (num_trans_string.length() < 4){
		num_trans_string = "0" + num_trans_string;
	    }
	    returnString += num_trans_string + " ";   
	return returnString;
    }

    //temp - Debugging print showing if there are any untrimmed spaces
    public String toStringDebug(){
	String returnString = "";
	returnString += "|" + this.number_ + "|";
	returnString += this.name_ + "|";
	returnString += this.status_ + "|";
	returnString += this.balance_ + "|";
	returnString += this.plan_ + "|";
	returnString += this.num_trans_ + "|";   
	return returnString;
    }
}





























