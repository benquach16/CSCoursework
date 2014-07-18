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
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include "Timer.h"

using namespace std;

//first method using streams
void getMethod(const char *inputfile, const char *outputfile)
{
  ifstream infile(inputfile);
  ofstream outfile(outputfile);
  char ch;
  while(infile.get(ch))
    {
      outfile.put(ch);
    }  
}

//use read() calls
void unixMethod(const char *inputfile, const char *outputfile)
{
  int infile = open(inputfile, O_RDONLY);
  int outfile = open(outputfile, O_WRONLY);
  char ch;
  bool stop = false;
  while(!stop)
    {
      int n = read(infile, &ch, 1);
      if(n == 0)
	{
	  stop = true;
	  break;
	}
      if(n == -1)
	{
	  //error is read
	  int code = errno;
	  cout << "read() failed with code: " << code << endl;
	  stop = true;
	}
      if(write(outfile, &ch, 1)==-1)
	{
	  int code = errno;
	  cout << "write() failed with code: " << code << endl;
	  stop = true;
	}
    }
  close(infile);
  close(outfile);
}

//similar to above
void unixBufMethod(const char *inputfile, const char *outputfile)
{
  int infile = open(inputfile, O_RDONLY);
  int outfile = open(outputfile, O_WRONLY);
  char ch[BUFSIZ];
  bool stop = false;
  while(!stop)
    {
      int n = read(infile, &ch, BUFSIZ);
      if(n == 0)
	{
	  stop = true;
	  break;
	}
      if(n == -1)
	{
	  //error is read
	  int code = errno;
	  cout << "read() failed with code: " << code << endl;
	  stop = true;
	}


      if(write(outfile, &ch, n)==-1)
	{
	  int code = errno;
	  cout << "write() failed with code: " << code << endl;
	  stop = true;
	}
    }
  close(infile);
  close(outfile);
}

int main(int argc, char* argv[])
{
  if(argc < 3)
    {
      //insufficient args
      cout << "need more arguments" << endl;
      return 1;
    }
  

  char *inputfile = argv[1];
  char *outputfile = argv[2];
  int n = 1;
  if(argc > 3)
    {
      //get n if it exists
      stringstream iss (argv[3]);
      iss >> n;
    }
  Timer t;
  double wallTime, userTime, sysTime;
  //start time
  
  t.start();
  for(unsigned i =0; i < n; i++)
    getMethod(inputfile, outputfile);
  t.elapsedTime(wallTime, userTime, sysTime);
  cout << "in.get() method" << endl;
  cout << "Wallclock Time: " << wallTime << " User Time: " << userTime << " System Time: " << sysTime << endl;
  cout << endl;
  t = Timer();
  t.start();
  for(unsigned i = 0; i < n; i++)
    unixMethod(inputfile, outputfile);
  t.elapsedTime(wallTime, userTime, sysTime);
  cout << "unix read() and write() methods char by char" << endl;
  cout << "Wallclock Time: " << wallTime << " User Time: " << userTime << " System Time: " << sysTime << endl;
  cout << endl;
  t = Timer();
  t.start();
  for(unsigned i = 0; i < n; i++)
    unixBufMethod(inputfile, outputfile);
  t.elapsedTime(wallTime, userTime, sysTime);
  cout << "unix read() and write() method with BUFSIZ buffer size" << endl;
  cout << "Wallclock Time: " << wallTime << " User Time: " << userTime << " System Time: " << sysTime << endl;
  cout << endl;
  return 0;
}

