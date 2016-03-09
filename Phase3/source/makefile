all: run
compile:
	g++-4.9 -std=c++11 main.cpp Account.cpp Account.h AccountsDatabase.cpp AccountsDatabase.h AccountConstants.h Transaction.cpp Transaction.h TransactionMapper.h TransactionWriter.cpp TransactionWriter.h CommandValidator.cpp CommandValidator.h TransactionHandler.h LogoutHandler.cpp LogoutHandler.h WithdrawalHandler.cpp WithdrawalHandler.h TransferHandler.cpp TransferHandler.h PaybillHandler.cpp PaybillHandler.h DepositHandler.cpp DepositHandler.h CreateHandler.cpp CreateHandler.h DeleteHandler.cpp DeleteHandler.h DisableHandler.cpp DisableHandler.h EnableHandler.cpp EnableHandler.h ChangeplanHandler.cpp ChangeplanHandler.h LoginHandler.cpp LoginHandler.h SessionStatus.h -o banksys 
run: compile
	./banksys test.cbaf temp.atf
clean:
	rm *~
