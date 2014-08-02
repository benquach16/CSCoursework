
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

#here be dragons
dircheck()
{
    for i in $@; do
	if [ -d $i ]
	    then
	    echo $i:
	    local dircount=0
    #not fond ofthis method
	    DIRS=$(find $i -maxdepth 1 -type d)
	    for n in $DIRS*; do
	        #make sure we subtract one because it takes itself into account
		((dircount++))
	    done
	    ((dircount--))
	#we just loop until we got a count
	    echo the number of subdirectories is $dircount
	    local filecount=0
	    FILES=$(find $i -maxdepth 1 -type f)
	    for n in $FILES; do
		((filecount++))
	    done
	    echo the number of files is $filecount
	#FIND ZERO LEN FILES ONLY IN CURRENT DIRECTORY!!!
	    ZEROLEN=$(find $i -maxdepth 1 -type f -size 0)
	    for n in $ZEROLEN; do
		echo $n is a zero-length file
	    done
	    du -s "$i"
	    echo
	else
	    echo $i is not a directory
	fi
    done
}

dircheck $@
