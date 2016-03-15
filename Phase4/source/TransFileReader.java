import java.io.*;
import java.util.ArrayList;

public class TransFileReader{
      
    public static ArrayList<Transaction> read(String[] trans_file_names){

      //create an ArrayList of Strings to hold all the transactions
      ArrayList<Transaction> transactions_list = new ArrayList<Transaction>();

	try {
	    //Create a writer for the merged transaction file
	    String merged_trans_file = "trans-files/mergedTransactions.tf";
	    File outFile = new File(merged_trans_file);
	    Writer writer = new BufferedWriter(
			    new OutputStreamWriter(
			    new FileOutputStream(outFile)));
	    
	    //Iterate through all the transaction files - ignore 1st since it is mbaf
	    for (int i = 1; i < trans_file_names.length; i++) {
		//read in the current transaction file
		InputStream in = new FileInputStream(trans_file_names[i]);
		Reader reader = new InputStreamReader(in, "UTF8");
		BufferedReader trans_file = new BufferedReader(reader);

		//variable that reads in every line from the transaction file
		String curr_trans_line = trans_file.readLine();

		//read the rest of the transaction file
		while(curr_trans_line != null){
		    //System.out.println(curr_trans_line); //temp
		    //push the transaction string onto the arraylist
		    transactions_list.add((new Transaction(curr_trans_line)));
		    writer.write(curr_trans_line + "\n");
		    //read the next line in the file
		    curr_trans_line = trans_file.readLine();
		}
		//close the current file being read in
		trans_file.close();
	    }
	    //close the outfile
	    writer.close();
	} catch (IndexOutOfBoundsException e) {
	    System.err.println("IndexOutOfBoundsException: " + e.getMessage());
	} catch (IOException e) {
	    System.err.println("Caught IOException: " + e.getMessage());
	}	

	//TEMP - read out all the transactions from the arraylist
	for (int i = 0; i < transactions_list.size(); i++){
	    //System.out.println(this.transactions_list.get(i));
	}
  
  return transactions_list;
    }
}
