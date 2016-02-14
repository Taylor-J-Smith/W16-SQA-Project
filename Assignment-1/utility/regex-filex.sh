#!/bin/bash

for filename in *.txt;
do
    echo $filename
    sed -i 's/please enter/[login] please enter/g' $filename
    sed -i 's/login success/[login] login success/g' $filename
    sed -i 's/logout success/[logout] Success!/g' $filename 
done

























































