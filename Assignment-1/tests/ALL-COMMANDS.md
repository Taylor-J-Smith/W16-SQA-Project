Welcome! type login to begin:

**Sample Transaction**
CC_AAAAAAAAAAAAAAAAAAAA_NNNNN_PPPPPPPP_MM
10 TESTSTUDENT3         99996 00000.00 S


**Bad user Input**
	#badinput!

#Login
10 ADMIN                00000 00000.00 A    #admin login
10 TESTUSER1            00001 00000.00 S    #standard login
[login] ERROR: ALREADY LOGGED IN
[login] ERROR: INVALID TRANSACTION COMMAND
[login] ERROR: NEED TO LOG IN FIRST
[login] ERROR: USERNAME DOES NOT EXIST
[login] please enter the type of account:
[login] please enter the account holder name:
[login] login success: testuser1

#Logout
[logout] ERROR: INVALID INPUT
[logout] ERROR: NEED TO LOG IN FIRST
[logout] Success!

#Withdrawal
01 TESTUSER1            00001 00001.00
[withdrawal] ERROR: NEED TO LOG IN FIRST
[withdrawal] ERROR: INVALID INPUT
[withdrawal] ERROR: ACCOUNT # DOES NOT MATCH HOLDER
[withdrawal] ERROR: AMOUNT EXCEEDS THE 500.00 LIMIT
[withdrawal] ERROR: INSUFFICIENT FUNDS
[withdrawal] Enter the account holder name:       #admin
[withdrawal] Enter the account number:
[withdrawal] Enter amount to withdraw:
[withdrawal] Success!

#Transfer
02 TESTUSER1            00001 00001.00
[transfer] ERROR: NEED TO LOG IN FIRST
[transfer] ERROR: INVALID INPUT
[transfer] ERROR: ACCOUNT # DOES NOT MATCH HOLDER
[transfer] ERROR: ACCOUNT HOLDER DOES NOT EXIST
[transfer] ERROR: AMOUNT EXCEEDS THE 1000.00 LIMIT
[transfer] ERROR: INSUFFICIENT FUNDS
[transfer] Enter the first account holder name:   #admin
[transfer] Enter the first account number:
[transfer] Enter the second account number:
[transfer] Enter amount to transfer:
[transfer] Success!


#Paybill
03 TESTUSER1            00001 00000.00
[paybill] ERROR: NEED TO LOG IN FIRST
[paybill] ERROR: ACCOUNT # DOES NOT MATCH HOLDER
[paybill] ERROR: ACCOUNT HOLDER DOES NOT EXIST
[paybill] ERROR: AMOUNT EXCEEDS THE 2000.00 LIMIT
[paybill] ERROR: INSUFFICIENT FUNDS
[paybill] ERROR: INVALID INPUT
[paybill] ERROR: NO COMPANY FOUND WITH THAT NAME
[paybill] Enter the account holder name:          #admin
[paybill] Enter the account number:
[paybill] Enter the company to pay:
[paybill] Enter amount to pay:
[paybill] Success!

#Deposit
04 TESTUSER1            00001 00000.00
[deposit] ERROR: NEED TO LOG IN FIRST
[deposit] ERROR: ACCOUNT # DOES NOT MATCH HOLDER
[deposit] ERROR: ACCOUNT HOLDER DOES NOT EXIST
[deposit] ERROR: AMOUNT EXCEEDS THE 2000.00 LIMIT
[deposit] ERROR: INSUFFICIENT FUNDS
[deposit] ERROR: INVALID INPUT
[deposit] Enter the account holder name:         #admin
[deposit] Enter the account number:
[deposit] Enter the amount to deposit:
[deposit] Success!

#create
[create] ERROR: NEED TO LOG IN FIRST
[create] ERROR: INVALID INPUT
[create] ERROR: PRIVILEGED ACCESS ONLY
[create] Enter the account holder name:
[create] Enter the initial balance:

#Delete
[delete] ERROR: NEED TO LOG IN FIRST
[delete] ERROR: INVALID INPUT
[delete] ERROR: PRIVILEGED ACCESS ONLY
[delete] Enter the account holder name:
[delete] Enter the account number:

#Disable
[disable] ERROR: NEED TO LOG IN FIRST
[disable] ERROR: INVALID INPUT
[disable] ERROR: PRIVILEGED ACCESS ONLY
[disable] Enter the account holder name:
[disable] Enter the account number:

#Enable
[enable] ERROR: NEED TO LOG IN FIRST
[enable] ERROR: INVALID INPUT
[enable] ERROR: PRIVILEGED ACCESS ONLY
[enable] ERROR: ACCOUNT ALREADY ENABLED
[enable] Enter the account holder name:
[enable] Enter the account number:
[enable] Account enabled successfully

#Changeplan
[changeplan] ERROR: NEED TO LOG IN FIRST
[changeplan] ERROR: INVALID INPUT
[changeplan] ERROR: PRIVILEGED ACCESS ONLY
[changeplan] Enter the account holder name:
[changeplan] Enter the account number:
[changeplan] Account plan changed successfully
