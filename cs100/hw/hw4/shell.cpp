/*
 * Course: CS 100 Fall 2013
 *
 * First Name: Benjamin
 * Last Name: Quach
 * Username: bquac002
 * email address: bquac002@ucr.edu
 *
 *
 * Assignment: hw4
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA. */


#include <iostream>
#include <string>
#include <vector>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

using namespace std;

vector<string> parse(string);
int execute(int, char*);

vector<string> parse(string s)
{
  vector<string> ret;
  //differentiate the line by spaces and endls
  for(unsigned i = 0; i < s.size(); i++)
    {
      if(s[i] == ' ' || s[i] == '\t' || s[i] == '<')
	{
	  //chop
	  
	  ret.push_back(s.substr(0, i));
	  if(s[i] == '<')
	    ret.push_back("<");
	  s.erase(0, i+1+(s[i]=='<'));
	  i = 0;
	}
    }
  //end didnt get chopped off so we just add it
  ret.push_back(s);
  return ret;
}

int loadFromBoth(int argc, char* args[])
{
  //input redirection
  int fd = open(args[2], O_RDWR);
  int fd2 = open(args[3], O_RDWR);

  if(fd == -1)
    {
      int errcode = errno;
      cout << "open() failed with error code : " << errcode << endl;
      exit(1);
    }
  int p[2];
  pid_t pid = fork();
  switch(pid)
    {
    case -1:
      {
	//error
	int errcode = errno;
	cout << "fork() failed with error code : " << errcode << endl;
	exit(1);
      }
    case 0:
      {
	//made a child
	//exec the argumen

	if(dup2(fd, 0)==-1)
	  {
	    int errcode = errno;
	    cout << "dup2() failed with error code : " << errcode << endl;
	  }
	
	dup2(fd2, 1);

	if(close(fd)==-1)
	  {
	    int errcode = errno;
	    cout << "close() failed with error code : " << errcode << endl;
	  }
	close(fd2);

	int n = execl(args[0], args[0], args[3], 0);

	if(n < 0)
	  {
	    int errcode = errno;
	    cout << "Exec() failed with code : " << errcode << endl;
	  }

	exit(1);
      }       
    default:
      {
	//parent proc so we have to wait
	if(close(fd)==-1)
	  {
	    int errcode = errno;
	    cout << "close() failed with error code : " << errcode << endl;
	  }
	close(fd2);

	int status;
	waitpid(-1, &status, 0);
      }
    }
  fd = open(args[2], O_RDWR);
  int fd3 = open(args[1], O_RDWR);
  if(fd == -1)
    {
      int errcode = errno;
      cout << "open() failed with code : " << errcode << endl;
    }
  pid = fork();
  switch(pid)
    {
    case -1:
      {
	int errcode = errno;
	cout << "fork() failed with code : " << errcode << endl;
      }
    case 0:
      {
	if(dup2(fd, 0)==-1)
	  {
	    int errcode = errno;
	    cout << "dup2() failed with error code : " << errcode << endl;
	  }
       	dup2(fd3, 1);

	if(close(fd)==-1)
	  {
	    int errcode = errno;
	    cout << "close() failed with error code : " << errcode << endl;
	  }
	close(fd3);

	int n = execl(args[0], args[0], args[1], 0);
	if(n < 0)
	  {
	    int errcode = errno;
	    cout << "Execl() call failed with code : " << errcode << endl;
	  }
	exit(1);
      }
    default:
      {
	int status;
	if(close(fd)==-1)
	  {
	    int errcode = errno;
	    cout << "close() failed with error code : " << errcode << endl;
	  }
	close(fd3);

	return waitpid(-1, &status, 0);
      }
    }
}

int loadFromLeft(int argc, char* args[])
{
  //input redirection
  int fd = open(args[1], O_WRONLY);

  int fd2 = open(args[2], O_RDONLY);
  if(fd2 == -1)
    {
      int errcode = errno;
      cout << "open() failed with error code : " << errcode << endl;
      exit(1);
    }
  int p[2];
  pid_t pid = fork();
  
  switch(pid)
    {
    case -1:
      {
	//error
	int errcode = errno;
	cout << "fork() failed with error code : " << errcode << endl;
	exit(1);
      }
    case 0:
      {
	//made a child
	//exec the argumen
	dup2(fd, 1);

	if(dup2(fd2, 0)==-1)
	  {
	    int errcode = errno;
	    cout << "dup2() failed with error code : " << errcode << endl;
	  }
	close(fd);

	if(close(fd2)==-1)
	  {
	    int errcode = errno;
	    cout << "close() failed with error code : " << errcode << endl;
	  }
	int n = execl(args[0], args[0], args[1], 0);
	if(n < 0)
	  {
	    int errcode = errno;
	    cout << args[0] << endl;
	    cout << "Exec() failed with code : " << errcode << endl;
	  }
	exit(1);
      }       
    default:
      {
	//parent proc so we have to wait
	close(fd);
	if(close(fd2)==-1)
	  {
	    int errcode = errno;
	    cout << "close() failed with error code : " << errcode << endl;
	  }
	int status;
	return waitpid(-1, &status, 0);
      }
    }
}


int execute(int argc, char *argv[])
{
  pid_t pid = fork();
  
  switch(pid)
    {
    case -1:
      {
	//error
	int errcode = errno;
	cout << "fork() failed with error code : " << errcode << endl;
	exit(1);
      }
    case 0:
      {
	//made a child
	//exec the argumen

	int n = execvp(argv[0], argv);
	if(n < 0)
	  {
	    int errcode = errno;
	    cout << "Exec() failed with code : " << errcode << endl;
	  }
	exit(1);
      }       
    default:
      {
	//parent proc so we have to wait

	int status;
	return waitpid(-1, &status, 0);
      }
    }  
}


int main(int argc, char * argv[])
{
  string prompt = "input : ";
  while(true)
    {
      cout << prompt;
      string input;
      getline(cin, input);
      vector<string> cmds = parse(input);
      //exec first arg
      //convert it to a char array of chars
      //and check if we have input output operands
      char *args[cmds.size()+1];
      for(unsigned i = 0; i < cmds.size(); i++)
	{
	  args[i] = (char*)cmds[i].c_str();
	}
      args[cmds.size()] = 0;
      vector<vector<string>> allCmds;

      for(unsigned i = 0; i < cmds.size(); i++)
	{
	  //check if we found a token
	  if(cmds[i] == "<" || cmds[i] == ">" || cmds[i] == "|")
	    {
	      vector<string> tmp;
	    }
	}
      
    }
  return 0;
}
