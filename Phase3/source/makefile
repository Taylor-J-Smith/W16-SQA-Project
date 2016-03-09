all: run
compile:
	g++-4.9 -std=c++11 main.cpp Account.cpp AccountsDatabase.cpp Transaction.cpp TransactionWriter.cpp CommandValidator.cpp LogoutHandler.cpp WithdrawalHandler.cpp TransferHandler.cpp PaybillHandler.cpp DepositHandler.cpp CreateHandler.cpp DeleteHandler.cpp DisableHandler.cpp EnableHandler.cpp ChangeplanHandler.cpp LoginHandler.cpp -o banksys 
run: compile
	./banksys test.cbaf temp.atf
clean:
	rm *~
