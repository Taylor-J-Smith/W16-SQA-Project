#!/bin/bash

if(( $# < 4)); then
    echo "<Directory><file-name><type><numFiles>"
    echo "example: ./create-files.sh login/in login in 9"
    echo "example: ./create-files.sh login/out login out 9"
    echo "example: ./create-files.sh login/trans login tf 9"
    exit
fi

DIRECTORY=$1
fileName=$2
type=$3
numFiles=$4

for (( i = 1 ; i <= $numFiles ; i++ ))
do
    if [ ! -d "$DIRECTORY" ]; then
	echo mkdir "$DIRECTORY"
	mkdir "$DIRECTORY"
    fi
    if(( $i < 10 )); then
	echo touch "$DIRECTORY"/"$fileName"0"$i".$type
	touch "$DIRECTORY"/"$fileName"0"$i".$type
    else
	echo touch "$DIRECTORY"/"$fileName$i".$type
	touch "$DIRECTORY"/"$fileName$i".$type
    fi
done
