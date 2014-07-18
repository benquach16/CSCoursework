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
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int NUM_INTERRUPT = 0;
int NUM_STOP = 0;
int NUM_QUIT = 0;

void getSignal(int, siginfo_t*, void*);


void getSignal(int signum, siginfo_t *info, void *pointer)
{
  switch(signum)
    {
    case SIGINT:
      {
	printf("I");
	NUM_INTERRUPT++;
	break;
      }
    case SIGQUIT:
      {
	printf("Q");
	NUM_QUIT++;
	break;
      }
    case SIGTSTP:
      {
	printf("S");
	NUM_STOP++;
	if(NUM_STOP>2)
	  {
	    cout << endl;
	    cout << "Interrupt: " << NUM_INTERRUPT << endl;
	    cout << "Stop: " << NUM_STOP << endl;
	    cout << "Quit: " << NUM_QUIT << endl;
	    exit(0);
	  }	

	kill(getpid(), SIGSTOP);
	break;
      }
    }

}


int main()
{
  //create sig struct
  struct sigaction sig;
  sig.sa_sigaction = getSignal;
  sigemptyset(&sig.sa_mask);
  sig.sa_flags = 0;
  sigaction(SIGINT, &sig, 0);
  sigaction(SIGTSTP, &sig, 0);
  sigaction(SIGQUIT, &sig, 0);
  while(true)
    {
      printf("X");

      if(NUM_INTERRUPT > 2)
	{
	  exit(0);
	}      
    }  
  return 0;
}
