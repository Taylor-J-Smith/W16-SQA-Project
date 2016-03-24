all: run
compile:
	javac -cp ../junit-4.10.jar:. *.java	

run: compile
	java backEnd old.mbaf trans-files/*.tf
test: compile
	java -cp ../junit-4.10.jar:. org.junit.runner.JUnitCore JUnitTest
clean:
	rm *.class
	rm *~
