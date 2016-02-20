#!/bin/bash

#example usage:  ./regex-filex.sh ../tests/02-withdrawl/out/

if(( $# < 1)); then
    echo "<PATH-to-out-dir>"
    echo "example: ./regex-filex.sh ../tests/02-withdrawl/out/"
    exit
fi

DIRPATH=$1

for filename in $DIRPATH*.out;
do
    echo $filename
    sed -i 's/please enter/[login] please enter/g' $filename
    sed -i 's/login success/[login] login success/g' $filename
    sed -i 's/logout success/[logout] Success!/g' $filename 
done

























































