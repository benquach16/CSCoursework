
# * Course: CS 100 Fall 2013
# *
# * First Name: Benjamin
# * Last Name: Quach
# * Username: bquac002
# * email address: bquac002@ucr.edu
# *
# *
# * Assignment: hw7
# *
# * I hereby certify that the contents of this file represent
# * my own original individual work. Nowhere herein is there
# * code from any outside resources such as another individual,
# * a website, or publishings unless specifically designated as
# * permissible by the instructor or TA. 

#!/bin/bash


IFS=':' read -ra P <<< "$PATH"
#P=('echo $PATH | tr ":" " "')
#find program within path
find()
{
    for i in $@; do
	local found=false
	for n in ${P[@]}; do
	    if [ -f $n/$i ]
		then
	        #found
		found=true
	        #make sure we dont habe double // marks
		if [[ $n != */ ]]
		    then
		    n="$n"/
		fi
		echo $n$i
	    fi
	done
	if [ "$found" == "false" ]
	    then
	    echo no $i in "("$PATH")"
	fi
    done
}

find $@
