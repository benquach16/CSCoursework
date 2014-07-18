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
      if(s[i] == ' ' || s[i] == '\t')
	{
	  //chop
	  ret.push_back(s.substr(0, i));

	  s.erase(0, i+1);
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
  int fd3 = open(args[1], O_RDWR);
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

	dup2(fd, 0);
	dup2(fd2, 1);
	close(fd);
	close(fd2);
	int n = execl(args[0], args[0], args[3], 0);

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
	close(fd2);
	int status;
	waitpid(-1, &status, 0);
      }
    }
  fd = open(args[2], O_RDWR);
  pid = fork();
  if(pid == 0)
    {
      dup2(fd, 0);
      dup2(fd3, 1);
      close(fd);
      close(fd3);
      execl(args[0], args[0], args[1], 0);
      exit(1);
    }
  else
    {
      int status;
      close(fd);
      close(fd3);
      return waitpid(-1, &status, 0);
    }
}

int loadFromLeft(int argc, char* args[])
{
  //input redirection
  int fd = open(args[1], O_RDWR);
  int fd2 = open(args[2], O_RDWR);
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
	dup2(fd2, 0);
	close(fd);
	close(fd2);
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
	close(fd2);
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
	  args[i] = (char*)cmds[i].c_str();
      args[cmds.size()] = 0;

      //make sure commands are right
      //if arg < arg2 then we do first
      if(cmds.size()>5)
	{
	  //assume < >
	  if(cmds[4]==">" && cmds[2] == "<")
	    {
	      char *arg[] = {args[0],
			     args[1],
			     args[3],
			     args[5], 0};
	      int c = 4;
	      loadFromBoth(c, arg);
	    }
	    
	}
      else if(cmds.size() > 2)
	{
	  if(cmds[2] == "<")
	    {
	      char *arg[] = {args[0],
			     args[1],
			     args[3], 0};
	      int c = 3;
	      loadFromLeft(c, arg);
	    }
	} 
      else
	execute(cmds.size(),args);
      
    }
  return 0;
}
