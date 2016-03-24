import static org.junit.Assert.*;
import junit.framework.JUnit4TestAdapter;
import org.junit.Test;

public class StackTest {
    @Test
    public void mytest() {
        Stack s = new Stack();
		s.push(5);
        assertEquals(5,s.peek());
    }
	@Test
	public void test2(){
		Stack r = new Stack();
		r.push(3);
		r.push(5);
		r.push(7);
		assertEquals(7,r.pop());
		assertEquals(r.peek(),5);
	}
    public static junit.framework.Test suite(){
       return new JUnit4TestAdapter(StackTest.class);
    }
}
