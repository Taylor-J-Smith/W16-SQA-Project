#!/bin/bash

counter=1
test_name=""
green="\033[1;32m" 
red="\033[1;31m"
reset_color="\033[0m"

cd tests
#iterate through all the different tests for each transaction
for i in *;
do
    cd $i
    #remove all the old test outputs
    rm -rf outputs/*
    cd in 
    ((counter=1)) #used to keep track of test number
    test_name=$(echo $i | cut -c 4-) #Obtain the name of the transaction
    for j in * #iterate through all the .in files
    do
	#test case for when counter is less than 10, we prefix the single digits with 0s
	if (($counter < 10)); then 
	    counter_string="0""$counter"
	else
	    counter_string=$counter
	fi

	##RUN THE TESTS
	../../../source/banksys ../../../source/test.cbaf ../outputs/"$test_name$counter_string".atf < "$test_name$counter_string".in > ../outputs/"$test_name$counter_string".out
	
	##COMPARE THE RESULTS

	#obtain the transaction file name
	tf_filename="../trans/"$test_name""$counter_string".tf"
	
	#ONLY IF THERE IS A TRANSACTION FILE CREATED
	if [ -f $tf_filename ]; then
	    #obtain the actual transaction file
	    tf_output="../outputs/$test_name$counter_string.atf"

	    #CHECK IF TRANSACTION FILES MATCH
	    #Check if the expected tf and and actual tf match
	    if  ! diff -q $tf_filename $tf_output > /dev/null; then
		echo "Transaction files are different"
		echo -e "$red$test_name$counter_string FAILED${reset_color}"
		atf_passed=false #test did not pass
	    else
		atf_passed=true #test passed
	    fi
	else
	    atf_passed=true #test passed
	fi

	#CHECK IF OUTPUT FILES MATCH
	expeced_output="../out/$test_name$counter_string.out"
	out_passed=false #set the output boolean to false	
	if [ "$atf_passed" = true ]; then #if transaction file passed
	    actual_output="../outputs/$test_name$counter_string.out"
	    #Check if the output files differ
	    if  ! diff -q $actual_output $expeced_output > /dev/null; then
	       echo "Output files are different"
	       echo -e "$red$test_name$counter_string FAILED${reset_color}"
	       out_passed=false #test failed
	   else
	       out_passed=true #test passed
	       echo -e "$green$test_name$counter_string PASSED${reset_color}"
	   fi
	fi
	##read debug
	((counter++)) #increment the counter
    done
    cd ../../
done



