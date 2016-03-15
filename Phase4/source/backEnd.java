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

	//read in all the transaction files
	TransFileReader trans_file_reader = new TransFileReader(args);
    }
}





























