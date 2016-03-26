import static org.junit.Assert.*;
import java.io.*;
import junit.framework.JUnit4TestAdapter;
import org.junit.Test;
import java.util.*;

/**
 * @author      ATT 
 * @version     1.0
 * @since       2016-03-26
 */

//A set of JUnit Test cases for the ____ method with decision and loop coverage
public class JUnitDecCov{
    
    @Test
    //Display what current JUnit file is running
    public void display(){
    }
    
    public static junit.framework.Test suite(){
	return new JUnit4TestAdapter(JUnitDecCov.class);
    }
}





























