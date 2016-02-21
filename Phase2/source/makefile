all: run
compile:
	g++ -std=c++11 main.cpp Account.cpp Account.h AccountsDatabase.cpp AccountsDatabase.h AccountConstants.h Transaction.cpp Transaction.h TransactionMapper.h TransactionWriter.cpp TransactionWriter.h CommandValidator.cpp CommandValidator.h TransactionHandler.h LogoutHandler.cpp LogoutHandler.h WithdrawalHandler.cpp WithdrawalHandler.h TransferHandler.cpp TransferHandler.h PaybillHandler.cpp PaybillHandler.h DepositHandler.cpp DepositHandler.h CreateHandler.cpp CreateHandler.h -o main
run: compile
	./main
clean:
	rm *~
