#!/bin/bash
#file2="file2.txt"

for file in *;
do
    if ! diff -q $1 $file > /dev/null
    then
	echo $1 "and " $file "are different"
	diff $1 $file >> "log.txt"
    else
	#echo "file and file_name are the same"
	echo $1 "and " $file "are the same"
    fi
done



























