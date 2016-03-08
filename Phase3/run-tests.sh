#!/bin/bash

counter=1
test_name=""
green="\e[1;32m" 
red="\e[1;31m"
reset_color="\033[0m"

cd tests
#iterate through all the different tests for each transaction
for i in *;
do
    cd $i
    #remove all the old test outputs
    rm -rf outputs/*
    cd in
    ((counter=1))
    test_name=$(echo $i | cut -c 4-)
    for j in *
    do
	if (($counter < 10)); then
	    counter_string="0""$counter"
	else
	    counter_string=$counter
	fi

	##RUN THE TESTS
	../../../source/banksys ../../../source/test.cbaf ../outputs/"$test_name$counter_string".atf < "$test_name$counter_string".in > ../outputs/"$test_name$counter_string".out
	
	##COMPARE THE RESULTSn
	#ONLY IF THERE IS A TRANSACTION FILE CREATED
	tf_filename="../trans/"$test_name""$counter_string".tf"
	
	if [ -f $tf_filename ]; then
	    tf_output="../outputs/$test_name$counter_string.atf"
	    if  ! diff -q $tf_filename $tf_output > /dev/null; then
		echo "Transaction files are different"
		echo -e "$red$test_name$counter_string FAILED${color_reset}"
		atf_passed=false
	    else
		atf_passed=true
	    fi
	else
	    atf_passed=true
	fi

	expeced_output="../out/$test_name$counter_string.out"
	out_passed=false	
	if [ "$atf_passed" = true ]; then
	    actual_output="../outputs/$test_name$counter_string.out"
	    if  ! diff -q $actual_output $expeced_output > /dev/null; then
	       echo "Output files are different"
	       echo -e "$red$test_name$counter_string FAILED${color_reset}"
	       out_passed=false
	   else
	       out_passed=true
	       echo -e "$green$test_name$counter_string PASSED${color_reset}"
	   fi
	fi
	read test
	((counter++))
    done
    cd ../../
done



