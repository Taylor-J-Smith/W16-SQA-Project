#!/bin/bash

if(( $# < 2)); then
  echo "Please pass in two arguements, the directory name, and number of files"
  exit
fi

DIRECTORY=$1
numFiles=$2

for (( i = 1 ; i <= $numFiles ; i++ ))
do
  if [ ! -d "$DIRECTORY" ]; then
    mkdir "$DIRECTORY"
  fi
  if(( $i < 10 )); then
      touch "$DIRECTORY"/IN-"$DIRECTORY"_test0"$i".txt
      touch "$DIRECTORY"/OUT-"$DIRECTORY"_test0"$i".txt
  else
    touch "$DIRECTORY"/IN-"$DIRECTORY"_test"$i".txt
    touch "$DIRECTORY"/OUT-"$DIRECTORY"_test"$i".txt
  fi
done
