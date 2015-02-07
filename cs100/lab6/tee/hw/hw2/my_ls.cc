/*
* Course: CS 100 Fall 2013
*
* First Name: Ben
* Last Name: Quach
* Username: bquac002
* email address: bquac002@ucr.edu
*
*
* Assignment: hw2
*
* I hereby certify that the contents of this file represent
* my own original individual work. Nowhere herein is there
* code from any outside resources such as another individual,
* a website, or publishings unless specifically designated as
* permissible by the instructor or TA. */

#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <vector>
#include <string>

using namespace std;

void readDir(char*, unsigned);
void readFile(char*, char*, unsigned);

void outputTabs(unsigned num)
{
  for(unsigned i = 0; i < num; i++)
    {
      cout << "    ";
    }
}

char* getReadablePermissions(mode_t st_mode)
{
  //interpret from the mode_t
  string ret;
  //directory field 
  if(S_ISDIR(st_mode))
    ret += 'd';
  else
    ret += '-';
  
  if(st_mode & S_IRUSR)
    ret += 'r';
  else
    ret += '-';
  
  if(st_mode & S_IWUSR)
      ret += 'w';
  else
    ret += '-';
  
  if(st_mode & S_IXUSR)
    ret += 'x';
  else
    ret += '-';

  //group permissions next
  if(st_mode & S_IRGRP)
    ret += 'r';
  else
    ret += '-';
  if(st_mode & S_IWGRP)
    ret += 'w';
  else
    ret += '-';
  if(st_mode & S_IXGRP)
    ret += 'x';
  else
    ret += '-';

  //other permissions
  if(st_mode & S_IROTH)
    ret += 'r';
  else
    ret += '-';
  if(st_mode & S_IWOTH)
    ret += 'w';
  else
    ret +='-';
  if(st_mode & S_IXOTH)
    ret += 'x';
  else
    ret += '-';
  
  return (char*)ret.c_str();
}

char *getReadableTime(time_t mtime)
{
  struct tm time;
  //load into struct
  localtime_r(&mtime, &time);
  char *ptr;
  char *format = "%b %e %R";
  strftime(ptr, 80, format,&time);
  return ptr;
}


void readDir(char *currentDirectory, unsigned indent = 0)
{
  DIR *dirp = 0;
  dirp = opendir(currentDirectory);
  if(!dirp)
    {
      cout <<currentDirectory << " Directory could not be opened" << endl;
      return;
    }
  //cout the stuff in it
  dirent *direntp;
  outputTabs(indent);
  cout << currentDirectory << ":" <<  endl;
  vector<char*> files;
  vector<char*> directories;
  while(direntp = readdir(dirp))
    {
      //readdir or readfile of each entry
      struct stat st;
      string str(currentDirectory);
      str+='/';
      str+=direntp->d_name;

      char *arg = (char*)str.c_str();
      if(stat(arg, &st) != 0)
	{
	  //  cout << "broke" << str.c_str() << endl;
	}
      if(direntp->d_name[0] != '.' && direntp->d_name[1] != '.')
	{
	  if(S_ISREG(st.st_mode))
	    {
	      
	      readFile(arg, direntp->d_name, indent+1);
	      files.push_back(arg);
	    }
	  else if(S_ISDIR(st.st_mode))
	    {
	      readDir(arg, indent+1);
	      directories.push_back(arg);
	    }
	}
    }
  cout << endl;
  closedir(dirp);
}

void readFile(char *filePath, char *name,  unsigned indent = 0)
{
  struct stat st;
  stat(filePath, &st);
  outputTabs(indent); 
  cout << getReadablePermissions(st.st_mode) << " " << st.st_nlink << " " << st.st_size 
       << " " << getReadableTime(st.st_mtime) << " " << name << endl;
}

int main(int argc, char *argv[])
{
  //we need to keep track of all the directories that is passed in by the args
  vector<char*> allDirs;
  vector<char*> allFiles;
  //get cmd line args
  
  for(int i = 1; i < argc; i++)
    {
      //find out if is a file or directory
      //then add it to th evector

      //struct we load stuff into
      struct stat st;
      if(stat(argv[i], &st) == 0)
	{
	  if(S_ISDIR(st.st_mode))
	    {
	      readDir(argv[i]);
	    }
	  else if(S_ISREG(st.st_mode))
	    {
	      readFile(argv[i], argv[i]);
	    }
	  else
	    {
	      cout << "invalid argument" << endl;
	    }
	}
    }
  if(argc == 1)
    {
      //no arguments so we add
      readDir(".");
    }
  return 0;
}
