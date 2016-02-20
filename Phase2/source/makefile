all: run
compile:
	g++ -std=c++11 main.cpp Account.cpp Account.h AccountsDatabase.cpp AccountsDatabase.h AccountConstants.h Transaction.cpp Transaction.h TransactionMapper.h -o main
run: compile
	./main
clean:
	rm *~
