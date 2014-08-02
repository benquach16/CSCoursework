#! /bin/bash
IFS=%
array[0]=test111
array[1]=test111
array[2]=hurrdurr
for i in ${#array}; do
    echo $i
done
