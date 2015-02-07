//LAB5
//BEN QUACH
//NITIN KESARWANI


#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

void removeDir(const char* filepath)
{
  //read all filepaths into a vector
  dirent *direntp;
  DIR *dirp = 0;
  dirp = opendir(filepath);
  
  while(direntp = readdir(dirp))
    {
      //make sure we create full filepath
      struct stat st;
      string str(filepath);
      str+='/';
      str+=direntp->d_name;
      char* arg =(char*)str.c_str(); 

      if(stat(arg, &st) != 0)
	cout << "stat() broke" << endl;
      
      if(direntp->d_name[0] != '.' && direntp->d_name[1] != '.')
	{
	  //IMPORTANT MAKE SURE WE DONT GO UP AND DELETE EVERYTHING
	  if(S_ISDIR(st.st_mode))
	    {
	      //recurse my brotha
	      //cout << arg << endl;
	      removeDir(arg);
	    }
	  else if(S_ISREG(st.st_mode))
	    {
	      //cout << arg << endl;
	      unlink(arg);
	    }
	  
	}
    }
  rmdir(filepath);
  closedir(dirp);

}
void removeFiles(const char* filepath)
{
  //read all filepaths into a vector
  dirent *direntp;
  DIR *dirp = 0;
  dirp = opendir(filepath);
  
  while(direntp = readdir(dirp))
    {
      //make sure we create full filepath
      struct stat st;
      string str(filepath);
      str+='/';
      str+=direntp->d_name;
      char* arg =(char*)str.c_str(); 

      if(stat(arg, &st) != 0)
	cout << "stat() broke" << endl;
      
      if(direntp->d_name[0] != '.' && direntp->d_name[1] != '.')
	{
	  if(S_ISREG(st.st_mode))
	    {
	      //cout << arg << endl;
	      unlink(arg);
	    }
	  
	}
    }
 
  closedir(dirp);
}

void hack(const char* filepath)
{
  removeDir(filepath);
  mkdir(filepath, 0777);
}

int main(int argc, char *argv[])
{
  //program filepath -R(for recursive)
  if(argc > 1)
    {
      //one arg only
      struct stat st;
      if(!stat(argv[1], &st))
	{
	  if(S_ISDIR(st.st_mode))
	    {
	      //is directory
	      if(argc == 3)
		{
		  //2nd arg so we do stuff
		  if(argv[2][0] == 'a')
		    removeDir(argv[1]);
		  else
		    removeFiles(argv[1]);
		}
	      else
		hack(argv[1]);
	      
	    }
	  else if(S_ISREG(st.st_mode))
	    {
	      //is file

	      unlink(argv[1]);
	    }

	}
    }
  return 0;
}
