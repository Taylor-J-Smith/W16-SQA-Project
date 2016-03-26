all: run
compile:
	javac -cp ../junit-4.10.jar:. *.java	

run: compile
	java backEnd old.mbaf trans-files/*.tf
test: test1 test2
test1: compile
	java -cp ../junit-4.10.jar:. org.junit.runner.JUnitCore JUnitStmtCov
test2: compile
	java -cp ../junit-4.10.jar:. org.junit.runner.JUnitCore JUnitDecCov
clean:
	rm *.class
	rm *~
