/*
 * Course: CS 100 Fall 2013
 *
 * First Name: Benjamin
 * Last Name: Quach
 * Username: bquac002
 * email address: bquac002@ucr.edu
 *
 *
 * Assignment: hw5
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA. */


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

using namespace std;

//setup global vars to save the stdin fds
int oldin, oldout;

//prototype functions
vector<string> parse(string);
int execute( char**);
void reredirect(vector<string> &args, bool dofork = true);
void piper(vector<vector<string> >&, int);
void handleBkgProc(int, siginfo_t *, void*);

void handleBkgProc(int signum, siginfo_t *info, void *pointer)
{
  if(signum == SIGCHLD)
    {
      cerr << "Child Process Ended " << getpid() << endl;
      exit(1);
    }
}
//HANDLE CHILD SIGNALS
void createAsBkg(vector<vector<string> >& splitByPipes, int procpid)
{
  int pid = fork();
  switch(pid)
    {
    case -1:
      {
	int errcode = errno;
	cerr << "fork() failed with code : " << errcode << endl;
      }
    case 0:
      {

	struct sigaction sig;
	sig.sa_sigaction = handleBkgProc;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGCHLD, &sig, 0);
	setsid();
	piper(splitByPipes, procpid);
	
      }
    default:
      {
	int status;
       	return;
      }
    }
}

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

void piper(vector<vector<string> > & args, int procpid)
{
  //we have to save the pid of the original proc so we dont accidently overwrite it
  if(args.size() == 1)
    {
      //just exec this man dont hurt me
      
      char *arg[args[0].size()];
      for(unsigned i = 0; i < args[0].size(); i++)
	{
	      
	  arg[i] = (char*)args[0][i].c_str();

	}
      arg[args[0].size()] = 0;
      //interpret what we need to do here ie redirect etc
      bool redir = false;
      for(unsigned i = 0; i < args[0].size(); i++)
	{
	  if(args[0][i] == "<" || args[0][i] == ">")
	    {
	      redir = true;
	      //redirect(arg[0], arg[i-1], arg[i+1], args[0][i]=="<");
	    }
	}
      if(!redir)
	execute(arg);
      else
	reredirect(args[0]);
      return;
	 
    }
  else
    {
      //do recursion
      //split dawgy dawg
      vector<string> c1 = args[0];
      args.erase(args.begin());
      int p[2];
      if(pipe(p) == -1)
	{
	  int errcode = errno;
	  cerr << "pipe() failed with code : " << errcode << endl;
	}
      int pid = fork();
      if(pid==0)
	{
	  if(close(p[1]) == -1)
	    {
	      int errcode = errno;
	      cerr << "failed to close p[1] with code : " << errcode << endl;
	    }
	  if(dup2(p[0], 0) == -1)
	    {
	      int errcode = errno;
	      cerr << "failed to dup2() with code : " <<errcode << endl;
	    }
	  if(close(p[0]) == -1)
	    {
	      int errcode = errno;
	      cerr << "failed to close with code : " << errcode << endl;
	    }
	  piper(args, procpid);
	}
      else if ( pid > 0 )
	{
	  //we want to exec in this proc
	  
	  if(getpid() == procpid)
	    {
	      if(close(p[0]) == -1)
		{
		  int errcode = errno;
		  cerr << "failed to close p[0] with code : " << errcode << endl;
		}
	      if(dup2(p[1], 1) == -1)
		{
		  int errcode = errno;
		  cerr << "failed to dup2() with code : " <<errcode << endl;
		}
	      if(close(p[1]) == -1)
		{
		  int errcode = errno;
		  cerr << "failed to close with code : " << errcode << endl;
		}
	      //how do we close it so all input stops
	      char *arg[c1.size()];
	      for(unsigned i = 0; i < c1.size(); i++)
		{
		  arg[i] = (char*)c1[i].c_str();
		}
	      arg[c1.size()] = 0;
	      
	      
	      //interpret what we need to do here ie redirect etc
	      bool redir = false;
	      for(unsigned i = 0; i < c1.size(); i++)
		{
		  if(c1[i] == "<" || c1[i] == ">")
		    {
		      redir = true;
		      //redirect(arg[0], arg[i-1], arg[i+1], c1[i]=="<");		      
		    }
		}
	      if(!redir)
		execute(arg);
	      else
		reredirect(c1);

	      if(close(0)==-1)
		{
		  int errcode = errno;
		  cerr << "close() failed with code : "<< errcode << endl;
		}
	      if(close(1)==-1)
		{
		  int errcode = errno;
		  cerr << "close() failed with code : "<< errcode << endl;
		}
	      //wait(0);
	      int status;
	      waitpid(-1, &status, 0);
	    }
	  else
	    {
	      //dont fork here
	      
	      if(close(p[0]) == -1)
		{
		  int errcode = errno;
		  cerr << "failed to close p[0] with code : " << errcode << endl;
		}
	      if(dup2(p[1], 1) == -1)
		{
		  int errcode = errno;
		  cerr << "failed to dup2() with code : " <<errcode << endl;
		}
	      if(close(p[1]) == -1)
		{
		  int errcode = errno;
		  cerr << "failed to close with code : " << errcode << endl;
		}
	      //how do we close it so all input stops
	      char *arg[c1.size()];
	      for(unsigned i = 0; i < c1.size(); i++)
		{
		  arg[i] = (char*)c1[i].c_str();
		}
	      arg[c1.size()] = 0;
	      
	      
	      //interpret what we need to do here ie redirect etc
	      bool redir = false;
	      for(unsigned i = 0; i < c1.size(); i++)
		{
		  if(c1[i] == "<" || c1[i] == ">")
		    {
		      redir = true;
		      //redirect(arg[0], arg[i-1], arg[i+1], c1[i]=="<",false);
		
		    }
		}
	      if(!redir)
		execvp(arg[0], arg);
	      else
		reredirect(c1, false);
	      
	      exit(1);
	    }
	}
      else
	{
	  //fork failed
	  int errcode = errno;
	  cerr << "fork() failed with code : " << errcode << endl;
	}
    }
}

void reredirect(vector<string> &args, bool dofork)
{
  //divide everything even further
  bool isinput = false;
  int inFd;
  string fdfile;
  for(unsigned i = args.size()-1; i > 0; i--)
    {
      if(args[i] == "<")
	{
	  //left side so we get the arg after it to act as stdin
	  fdfile = args[i+1];
	  int fd = open((char*)args[i+1].c_str(), O_RDONLY);
	  if(fd == -1)
	    {
	      int errcode = errno;
	      cerr << "open() failed with code : " << errcode << endl;
	    }
	  inFd = fd;
	  isinput = true;
	  if(dofork)
	    {
	      int pid = fork();
	      if(pid == 0)
		{
		  //take everything before i as an arg
		  //everything before this is an arg
		  if(dup2(fd, STDIN_FILENO) == -1)
		    {
		      int errcode = errno;
		      cerr << "dup() failed with code : " << errcode << endl;
		    }
		  
		  if(close(fd) == -1)
		    {
		      int errcode = errno;
		      cerr << "close() failed with code : " << errcode << endl;
		    }
		  //massive argument modification
		  //flip the args!!!!!!!
		  vector<string> tmp;
		  for(unsigned n = i-1; n > 0; n--)
		    {
		      
		      if(args[n] != "<" && args[n] != ">")
			{
			  tmp.push_back(args[n]);
			}
		      else
			break;
		    }
		  tmp.push_back(args[0]);
		  //flip tmp
		  std::reverse(tmp.begin(), tmp.end());
		  char *arg[tmp.size()];
		  for(unsigned n = 0; n < tmp.size(); n++)
		    {
		      arg[n] = (char*)tmp[n].c_str();

		    }
		  arg[tmp.size()] = 0;
		  if(execvp(arg[0], arg)==-1)
		    {
		      int errcode = errno;
		      cerr << "execvp() failed with code : " << errcode << endl;
		    }
		  exit(0);
		}
	      else if (pid > 0)
		{
		  //parent
		  //remove this from args
		  close(fd);
		  int status;
		  waitpid(-1, &status, 0);
		}
	      else
		{
		  //error
		  int errcode = errno;
		  cerr << "fork() failed with code : " << errcode << endl;
		}
	    }
	  else
	    {
	      //take everything before i as an arg
	      //everything before this is an arg
	      if(dup2(fd, STDIN_FILENO) == -1)
		{
		  int errcode = errno;
		  cerr << "dup2() call failed with code : " << errcode << endl;
		}

	      //massive argument modification
	      //flip the args!!!!!!!
	      vector<string> tmp;
	      for(unsigned n = i-1; n > 0; n--)
		{
		      
		  if(args[n] != "<" && args[n] != ">")
		    {
		      tmp.push_back(args[n]);
		    }
		  else
		    break;
		}
	      tmp.push_back(args[0]);
	      //flip tmp
	      std::reverse(tmp.begin(), tmp.end());
	      char *arg[tmp.size()];
	      for(unsigned n = 0; n < tmp.size(); n++)
		{
		  arg[n] = (char*)tmp[n].c_str();

		}
	      arg[tmp.size()] = 0;
	      if(execvp(arg[0], arg)==-1)
		{
		  int errcode = errno;
		  cerr << "execvp() failed with code : " << errcode << endl;
		}
	      exit(0);
	    }

	}
      else if(args[i] == ">")
	{
	  //right side so we save the arg as stdout	  
	  int fd = open(args[i+1].c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR);

	  if(fd == -1)
	    {
	      int errcode = errno;
	      cerr << "open() failed with code : " << errcode << endl;
	    }
	  if(dofork)
	    {
	      int pid = fork();
	      if(pid == 0)
		{
		  if(dup2(fd, STDOUT_FILENO)==-1)
		    {
		      int errcode = errno;
		      cerr << "dup2() failed with code : " << errcode << endl;
		    }
		  if(isinput)
		    {
		      int fd2 = open(fdfile.c_str(), O_RDONLY);
		      if(fd2 == -1)
			{
			  int errcode = errno;
			  cerr << "open() failed with code : " << errcode << endl;
			}
		      if(dup2(fd2, STDIN_FILENO) == -1)
			{
			  int errcode = errno;
			  cerr << "dup2() failed with code : " << errcode << endl;
			}
		      
		      if(close(fd2)==-1)
			{
		      
			  int errcode = errno;
			  cerr << "close() failed with code : " << errcode << endl;
			}
		    }

		  if(close(fd)==-1)
		    {
		      
		      int errcode = errno;
		      cerr << "close() failed with code : " << errcode << endl;
		    }
		  //massive argument modification
		  //flip the args!!!!!!!
		  vector<string> tmp;
		  for(unsigned n = i-1; n > 0; n--)
		    {
		      
		      if(args[n] != "<" && args[n] != ">")
			{
			  tmp.push_back(args[n]);
			}
		      else
			break;
		    }
		  tmp.push_back(args[0]);
		  //flip tmp
		  std::reverse(tmp.begin(), tmp.end());
		  char *arg[tmp.size()];
		  for(unsigned n = 0; n < tmp.size(); n++)
		    {
		      arg[n] = (char*)tmp[n].c_str();

		    }
		  arg[tmp.size()] = 0;
		  if(execvp(arg[0], arg)==-1)
		    {
		      int errcode = errno;
		      cerr << "execvp() failed with code : "<< errcode << endl;
		    }
		  exit(0);
		}
	      else if(pid > 0)
		{
		  //parent
		  //remove this from args

		  if(close(fd)==-1)
		    {
		      
		      int errcode = errno;
		      cerr << "close() failed with code : " << errcode << endl;
		    }
		  int status;
		  waitpid(-1, &status, 0);
		}
	      else
		{
		  //error
		  int errcode = errno;
		  cerr << "fork() failed with code : " << errcode << endl;
		}
	    }
	  else
	    {
	      //replace this proc

	      if(dup2(fd, STDOUT_FILENO) == -1)
		{
		  int errcode = errno;
		  cerr << "dup2() failed with code : " << errcode << endl;
		}
	      if(isinput)
		{
		  int fd2 = open(fdfile.c_str(), O_RDONLY);
		  if(fd2 == -1)
		    {
		      int errcode = errno;
		      cerr << "open() failed with code : " << errcode << endl;
		    }
		  if(dup2(fd2, STDIN_FILENO) == -1)
		    {
		      int errcode = errno;
		      cerr << "dup2() failed with code : " << errcode << endl;
		    }
		  if(close(fd2) == -1)
		    {
		      int errcode = errno;
		      cerr << "close() failed with code : " << errcode << endl;
		    }
		}
	      if(close(fd)==-1)
		{
		  
		  int errcode = errno;
		  cerr << "close() failed with code : " << errcode << endl;
		}

	      //massive argument modification
	      //flip the args!!!!!!!
	      vector<string> tmp;
	      for(unsigned n = i-1; n > 0; n--)
		{
		      
		  if(args[n] != "<" && args[n] != ">")
		    {
		      tmp.push_back(args[n]);
		    }
		  else
		    break;
		}
	      tmp.push_back(args[0]);
	      //flip tmp
	      std::reverse(tmp.begin(), tmp.end());
	      char *arg[tmp.size()];
	      for(unsigned n = 0; n < tmp.size(); n++)
		{
		  arg[n] = (char*)tmp[n].c_str();

		}
	      arg[tmp.size()] = 0;
	      if(execvp(arg[0], arg)==-1)
		{
		  int errcode = errno;
		  cerr << "execvp() failed with code : " << errcode << endl;
		}
	      exit(0);
	    }
	}
    }
}

int execute(char *argv[])
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
  //make sure we save the file descriptors before we annihilate them
  oldin = dup(STDIN_FILENO);
  oldout = dup(STDOUT_FILENO);

  while(true)
    {
      cout << prompt;
      string input;
      getline(cin, input);
      vector<string> cmds = parse(input);
      //exec first arg
      //convert it to a char array of chars
      //and check if we have input output operands


      //make sure commands are right
      //if arg < arg2 then we do first
      //lets do something different, we for loop through the
      //arguments so we can interactively create redirection
      bool bkg = false;
      if(cmds[cmds.size()-1] == "&")
	{
	  //create this as a background

	  cmds.pop_back();
	  bkg = true;
	}
      char *args[cmds.size()+1];
      for(unsigned i = 0; i < cmds.size(); i++)
	{
	  args[i] = (char*)cmds[i].c_str();
	}
      args[cmds.size()] = 0;
      vector<vector<string> > splitByPipes;
      
      while(!cmds.empty())
	{
	  vector<string> ret;
	  while(!cmds.empty())
	    {
	      if(cmds[0] != "|")
		{
		  ret.push_back(cmds[0]);
		  cmds.erase(cmds.begin());
		}
	      else
		{
		  //make sure we delete the operator
		  if(cmds[0] == "<" || cmds[0] == ">")
		    {
		      ret.push_back(cmds[0]);
		      cmds.erase(cmds.begin());
		    }
		  else
		    {
		      //if we came across a pipe
		      //we break the loopp
		      cmds.erase(cmds.begin());
		      break;
		    }
		}
	    }
	  splitByPipes.push_back(ret);
	}
      if(bkg)
	createAsBkg(splitByPipes, getpid());
      else
	piper(splitByPipes, getpid());

      dup2(oldin, STDIN_FILENO);
      dup2(oldout, STDOUT_FILENO);

    }
  return 0;
}
