import static org.junit.Assert.*;
import junit.framework.JUnit4TestAdapter;
import org.junit.Test;

public class JUnitTest {
    @Test
    public void mytest() {
        assertEquals(5,5);
    }

    public static junit.framework.Test suite(){
       return new JUnit4TestAdapter(JUnitTest.class);
    }
}
