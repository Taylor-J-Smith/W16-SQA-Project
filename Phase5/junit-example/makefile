all: compile run
compile:
	javac -cp ../junit-4.10.jar:. Stack.java
	javac -cp ../junit-4.10.jar:. StackTest.java 
run:
	java -cp ../junit-4.10.jar:. org.junit.runner.JUnitCore StackTest

clean:
	rm *.class	
