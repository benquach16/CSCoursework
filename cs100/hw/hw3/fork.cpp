/*
 * Course: CS 100 Fall 2013
 *
 * First Name: Benjamin
 * Last Name: Quach
 * Username: bquac002
 * email address: bquac002@ucr.edu
 *
 *
 * Assignment: hw3
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA. */

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
using namespace std;

const int ITERATIONS = 10000;

void parentProc()
{
  for(unsigned i = 0; i < ITERATIONS; i++)
    {
      cout << "A" << flush;
    }
  cout << endl;
  cout.flush();
}

void childProc(int increment)
{
  char letter = 'A';
  letter += increment;
  for(unsigned i = 0; i < ITERATIONS; i++)
    {
      cout << letter << flush;
    }
  cout << endl;
  cout.flush();
}

int main()
{
  //fork 2^2 processes aka 4
  //cout << "Parent Process PID:" << getpid() << endl;
  //parentProc();
  /*
  //create a pipe
  int p[2];
  int numChild=0;
  
  int n = pipe(p);
  
  if(n < 0)
    {
      //if its -1 we exit
      int errcode = errno;
      cout << "pipe() failed with code: " << errcode << endl;
      return 1;
    }
  */
  
  int pid;
  int childPid[4] = {0,0,0,0};
  int status;
  for(int i = 0; i < 4; i++)
    {
      pid = fork();
      if(!pid)
	{
	  //child
	  cout << "Created Child PID: " << getpid() << endl;
	  char letter = 'A';
	  letter += i;
	  for(unsigned n = 0; n < ITERATIONS; n++)
	    {
	      cout << letter <<flush;
	    }
	  break;
	  
	}
      else if(pid > 0)
	{
	  //parent
	  cout << "Parent PID: " << getpid() << endl;
	  childPid[i] = pid;
	}
      else if(pid < 0)
	{
	  //error handling
	  int errcode = errno;
	  cout << "fork() failed with code: " << errcode << endl;
	}
    }
  
  for(int i = 0; i < 4; i++)
    wait(0);
  return 0;
}
