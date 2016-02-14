#!/bin/bash

if(( $# < 2)); then
    echo "<Name><numFiles>"
    echo ./create-files.sh logout 3
    exit
fi

NAME=$1
numFiles=$2

echo mkdir "$NAME"
echo mkdir "$NAME/in"
echo mkdir "$NAME/out"
echo mkdir "$NAME/trans"
echo mkdir "$NAME"
mkdir "$NAME"
mkdir "$NAME/in"
mkdir "$NAME/out"
mkdir "$NAME/trans"

for (( i = 1 ; i <= $numFiles ; i++ ))
do
    #if [ ! -d "$NAME" ]; then

#    fi
    if(( $i < 10 )); then
	echo touch "$NAME/in/$NAME"0"$i".in
	echo touch "$NAME/out/$NAME"0"$i".out
	echo touch "$NAME/trans/$NAME"0"$i".tf
	touch "$NAME/in/$NAME"0"$i".in
	touch "$NAME/out/$NAME"0"$i".out
	touch "$NAME/trans/$NAME"0"$i".tf
    else
	echo touch "$NAME/in/$NAME$i".in
	echo touch "$NAME/out/$NAME$i".out
	echo touch "$NAME/trans/$NAME$i".tf
	touch "$NAME/in/$NAME$i".in
	touch "$NAME/out/$NAME$i".out
	touch "$NAME/trans/$NAME$i".tf
    fi
done
