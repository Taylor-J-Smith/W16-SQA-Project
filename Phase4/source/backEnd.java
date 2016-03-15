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

	//create an ArrayList of Strings to hold all the transactions
	ArrayList<String> transactions_list = new ArrayList<String>();

	TransFileReader trans_file_reader = new TransFileReader(args);
	try {
	    //Iterate through all the transaction files
	    //int num_trans_files = args.length - 1; //1 of the arguments is the mbaf
	    for (int i = 1; i < args.length; i++) {
		//read in the current transaction file
		InputStream in = new FileInputStream(args[i]);
		Reader reader = new InputStreamReader(in, "UTF8");
		BufferedReader trans_file = new BufferedReader(reader);

		//variable that reads in every line from the transaction file
		String curr_trans_line = trans_file.readLine();

		//read the rest of the transaction file
		while(curr_trans_line != null){
		    //System.out.println(curr_trans_line); //temp
		    //push the transaction string onto the arraylist
		    transactions_list.add(curr_trans_line);
		    curr_trans_line = trans_file.readLine();
		}
		//close the current file being read in
		trans_file.close();
	    }
	} catch (IndexOutOfBoundsException e) {
	    System.err.println("IndexOutOfBoundsException: " + e.getMessage());
	} catch (IOException e) {
	    System.err.println("Caught IOException: " + e.getMessage());
	}

	//TEMP - read out all the transactions from the arraylist
	for (int i = 0; i < transactions_list.size(); i++){
	    //System.out.println(transactions_list.get(i));
	}
    }
}





























