/*
 * Course: CS 100 Fall 2013
 *
 * First Name: Benjamin
 * Last Name: Quach
 * Username: bquac002
 * email address: bquac002@ucr.edu
 *
 *
 * Assignment: hw6
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
#include <dirent.h>

using namespace std;

//setup global vars to save the stdin fds
int oldin, oldout;
int parpid;
//prototype functions
//we're going to need a bigger list
vector<string> parse(string);
int execute( char**);
void reredirect(vector<string> &args, bool dofork = true);
void execFunction(vector<string> args, bool dofork = true);
void reexecFunction(vector<string> args, int i);
void piper(vector<vector<string> >&, int);
void handleBkgProc(int, siginfo_t *, void*);
char* getPathFilename(char * path);
//we need 'error' functions, to handle posix functions
//pretty redundant but have to thave them
void handleDup2(int ret)
{
  if(ret == -1)
    {
      int errcode = errno;
      cout << "dup2() function failed with error code : " << errcode << endl;
      exit(1);
    }
}
void handleClose(int ret)
{
  if(ret == -1)
    {
      int errcode = errno;
      cout << "close() function failed with error code : " << errcode << endl;
      exit(1);
    }
}
void handleOpen(int ret)
{
  if(ret == -1)
    {
      int errcode = errno;
      cout << "open() function failed with error code : " << errcode << endl;
      exit(1);
    }
}
void handleExec(int ret)
{
  if(ret == -1)
    {
      int errcode = errno;
      cout << "exec() function failed with error code : " << errcode << endl;
      exit(1);
    }
}


//make the path vector a global
//since constantly parsing it is slow
//we want the scope to be global so this is fine
vector<string> pathList;

vector<string> parsePATH()
{
  char* path = getenv("PATH");
  //parse
  vector<string> ret;
  char *pch = strtok(path, ":");
  while(pch)
    {
      //append '/' to the end of the path so we can just append filepath
      //make sure that there isn't already a / though!!!
      //strcat(pch, "/");
      string t(pch);
      if(t[t.size()-1] != '/')
	t += '/';
      //cout << t << endl;
      ret.push_back(t);
      pch = strtok(0, ":");
      
    }
  return ret;
}

char* getPathFilename(char * path)
{

  struct stat sta;
  if(!stat(path,&sta) && S_ISREG(sta.st_mode))
    return path;
  //check if path exists
  //the current directory is technically in path so we dont have to check
  vector<string> p = pathList;
  for(unsigned i = 0 ; i < p.size(); i++)
    {
      //append and test if it exists
      string t(p[i]);
      t+=path;
      //cerr << t << endl;
      struct stat st;
      if(stat(t.c_str(), &st) == 0 && S_ISREG(st.st_mode))
	{
	  //file exists
	  return (char*)t.c_str();
	}
    }
  return path;
}

void handleBkgProc(int signum, siginfo_t *info, void *pointer)
{
  if(signum == SIGCHLD)
    {
      cout << "Child Process Ended " << getpid() << endl;
      exit(1);
    }
  if(signum == SIGINT)
    {
      //force a child to go to the background
      
      cout << endl;
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

void execFunction(vector<string> args, bool dofork)
{

  //just exec this man dont hurt me
      
  char *arg[args.size()];
  for(unsigned i = 0; i < args.size(); i++)
    {
	      
      arg[i] = (char*)args[i].c_str();

    }
  arg[args.size()] = 0;
  execute(arg);
}

void reexecFunction(vector<string> args, int i)
{
  //for redirection
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
  handleExec(execv(arg[0], arg));
}

void piper(vector<vector<string> > & args, int procpid)
{
  //we have to save the pid of the original proc so we dont accidently overwrite it
  if(args.size() == 1)
    {
      execFunction(args[0]);
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
	  handleClose(close(p[1]));
	  handleDup2(dup2(p[0], 0));
	  handleClose(close(p[0]));

	  piper(args, procpid);
	}
      else if ( pid > 0 )
	{
	  //we want to exec in this proc
	  handleClose(close(p[0]));
	  handleDup2(dup2(p[1], 1));
	  handleClose(close(p[1]));	  
	  if(getpid() == procpid)
	    {
	      //how do we close it so all input stops
	      execFunction(c1);
	      handleClose(close(0));
	      handleClose(close(1));

	      //wait(0);
	      int status;
	      waitpid(-1, &status, 0);
	    }
	  else
	    {
	      //dont fork here

	      execFunction(c1, false);
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
	  handleOpen(fd);
	  inFd = fd;
	  isinput = true;
	  if(dofork)
	    {
	      int pid = fork();
	      if(pid == 0)
		{
		  //take everything before i as an arg
		  //everything before this is an arg
		  handleDup2(dup2(fd, STDIN_FILENO));
		  
		  handleClose(close(fd));
		  reexecFunction(args, i);
		  exit(0);
		}
	      else if (pid > 0)
		{
		  //parent
		  //remove this from args
		  handleClose(close(fd));
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
	      handleDup2(dup2(fd, STDIN_FILENO));
	      reexecFunction(args, i);
	      exit(0);
	    }

	}
      else if(args[i] == ">")
	{
	  //right side so we save the arg as stdout	  
	  int fd = open(args[i+1].c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR);
	  handleOpen(fd);
	  if(dofork)
	    {
	      int pid = fork();
	      if(pid == 0)
		{
		  handleDup2(dup2(fd, STDOUT_FILENO));

		  if(isinput)
		    {
		      int fd2 = open(fdfile.c_str(), O_RDONLY);
		      handleOpen(fd2);
		      handleDup2(dup2(fd2, STDIN_FILENO));
		      
		      handleClose(close(fd2));
		    }

		  handleClose(close(fd));
		  reexecFunction(args, i);
		  exit(0);
		}
	      else if(pid > 0)
		{
		  //parent
		  //remove this from args

		  handleClose(close(fd));
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
	      handleDup2(dup2(fd, STDOUT_FILENO));
	      if(isinput)
		{
		  int fd2 = open(fdfile.c_str(), O_RDONLY);
		  handleOpen(fd2);
		  handleDup2(dup2(fd2, STDIN_FILENO));
		  handleClose(close(fd2));
		}
	      handleClose(close(fd));
	      reexecFunction(args, i);
	      exit(0);
	    }
	}
    }
}

int execute(char *argv[])
{
  pid_t pid = fork();
  
  argv[0] = getPathFilename(argv[0]);
  //for some reason there is a random 0
  //get rid of it
  argv[0] = strtok(argv[0], "0");

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
	//exec the argument
	//cant just function this cause each siaction does different things
	struct sigaction sig;
	sig.sa_handler = SIG_DFL;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, 0);
	int n = execv(argv[0], argv);
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
  pathList = parsePATH();
  parpid = getpid();
  struct sigaction sig;
  sig.sa_sigaction = handleBkgProc;
  sigemptyset(&sig.sa_mask);
  sig.sa_flags = 0;
  sigaction(SIGINT, &sig, 0);

  while(true)
    {
      fputs("input: ", stdout);
      char input[80];
      fgets(input, 80, stdin);
      string t;
      for(unsigned i = 0; i < strlen(input); i++)
	t+=input[i];
      t[t.size()-1] = '\0';
      vector<string> cmds = parse(t);
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
      //ensure we do different things with &
      if(bkg)
	createAsBkg(splitByPipes, getpid());
      else
	piper(splitByPipes, getpid());

      dup2(oldin, STDIN_FILENO);
      dup2(oldout, STDOUT_FILENO);

    }
  return 0;
}
