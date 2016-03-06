#!/bin/bash

counter=1
test_name=""
cd tests

for i in *;
do
    cd $i
    cd in
    ((counter=1))
    test_name=$(echo $i | cut -c 4-)
    for j in *
    do
	if (($counter < 10)); then
	    ../../../source/banksys ../../../source/test.cbaf ../outputs/"$test_name"0"$counter".atf < "$test_name"0"$counter".in > ../outputs/"$test_name"0"$counter".out	   
	else
	    ../../../source/banksys ../../../source/test.cbaf ../outputs/"$test_name$counter".atf < "$test_name$counter".in > ../outputs/"$test_name$counter".out	   
	fi
	#read temp
	#echo $counter
	((counter++))
    done
    cd ../../
done


#echo “running test $i”
#banksys currentaccounts.txt ../outputs/$i.atf < $i > ../outputs/$i.out






























