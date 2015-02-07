//LAB5
//BEN QUACH
//NITIN KESARWANI

#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[])
{
  if(argc == 3)
    {
      struct stat st;
      if(!stat(argv[1], &st))
	{
	  if(S_ISREG(st.st_mode))
	    {
	      link(argv[1], argv[2]);
	      unlink(argv[1]);
	    }
	  else if(S_ISDIR(st.st_mode))
	    {
	      link(argv[1], argv[2]);
	      rmdir(argv[1]);
	    }
	}
    }   
   return 0;
}
	
