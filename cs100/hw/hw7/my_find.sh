
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

#the first arg is the directory

DIR="."
founddir=false
types=false
directory=false
counter=0
usepattern=false
pattern=""
print=false
exec=false
execpath=""
declare -a execargs
execreplace=false
exechasargs=false

#parse all other arguments
for i in $@; do

    ((counter++))
    if [ "$i" == "-type" ]
	then
	tmp=counter
	((tmp++))
	types=true
	#get the next arg
	if [ "${!tmp}" == "d" ]
	    then
	    directory=true
	fi
    fi

    if [ "$i" == "-name" ]
	then
	usepattern=true
	tmp=counter
	((tmp++))
	pattern=${!tmp}

    fi

    if [ "$i" == "-exec" ]
	then
	#we found the exec
	#arg after this will be the program
	tmp=counter
	((tmp++))
	exec=true
	execpath=${!tmp}
	((tmp++))
	#if we find {} or a filepath we stop
	#everything before it is an arg for the exec

	i=0
	while [ "${!tmp}" != "\;" ]; do
	    execargs[i]=${!tmp}
	    echo ${!tmp}
	    ((i++))
	    ((tmp++))
	done
	for n in ${execargs[*]}; do
	    echo $n
	done
    fi
    if [ "$i" == "-print" ]
	then
	#we just set a flag
	print=true
    fi
    if [ -d $i ]
	then
	#we found the directory we search in
	if [ "$founddir" == "false" ]
	    then
	    DIR=$i
	    founddir=true
	fi
    fi
done

function checktypes()
{

    if [ "$types" == "true" ]
	then
	    #if we check types then printout only the type
	if [ "$directory" == "true" ]
	    then
	    if [ -d $1 ]
		then
		return 1
	    else
		return 0
	    fi
	else
	    if [ -f $1 ]
		then
		return 1
	    else
		return 0
	    fi

	fi
    else
	return 1
    fi
}

#here be dragons.
function isvalid()
{
    if [ "$usepattern" == "true" ]
	then
	if [ "${1##*/}" == "$pattern" ]
	    then
	    checktypes $1
	    return 1
	else
	    return 0
	fi
    else
	checktypes $1
	return $?
    fi
    
}

print()
{
    local i
    for i in $1/*; do    
	isvalid $i
	ret=$?
	if [ $ret -eq 1 ]
	    then
	    if [ "$exec" == "true" ]
		then
		if [ "$print" == "true" ]
		    then
		    echo $i
		fi
		if [ "$exechasargs" == "true" ]
		    then
		    [ "$execreplace" == "true" ] && exec $execpath $execargs $i
		    [ "$execreplace" != "true" ] && exec $execpath $execargs
		else
		    [ "$execreplace" == "true" ] && exec $execpath $i
		fi
	    else
		echo $i
	    fi
	fi
	[ -d "$i" ] && print "$i"
    done
}

print $DIR
