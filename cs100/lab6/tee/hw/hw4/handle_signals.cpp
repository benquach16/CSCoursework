#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int NUM_INTERRUPT = 0;
int NUM_STOP = 0;
int NUM_QUIT = 0;

void getSignal(int, siginfo_t*, void*);
void loop();

void getSignal(int signum, siginfo_t *info, void *pointer)
{
  cout << "Got Signal " << signum << endl;
  fflush(stdout);
  NUM_INTERRUPT++;
  
  return;
}

void loop()
{

  while(true)
    {
      cout << NUM_INTERRUPT << flush;

      if(NUM_INTERRUPT > 2)
	{
	  exit(1);
	}      
    }  
}

int main()
{

  struct sigaction sig;
  sig.sa_sigaction = getSignal;

  sigaction(SIGINT, &sig, 0);
  loop();
  return 0;
}
