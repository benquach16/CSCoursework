/*

* Course: CS 100 Fall 2013

*

* First Name: Benjamin
* 
* Last Name: Quach

* Username: bquac002

* email address: bquac002@ucr.edu

*

*

* Assignment: hw1
*

* I hereby certify that the contents of this file represent

* my own original individual work. Nowhere herein is there

* code from any outside resources such as another individual,

* a website, or publishings unless specifically designated as

* permissible by the instructor or TA.

*/

#include "stack.h"

#include <string>
#include <iostream>

using namespace std;

//implementation
Stack::Stack() : size(0), data(new char[STACK_CAPACITY])
{
	
}

void Stack::push(char c)
{
  if(size < STACK_CAPACITY)
    {
      data[size] = c;
      size++;
    }
  else
    {
      cout << "stack full" <<endl;
    }
}

char Stack::pop()
{
  if(size > 0)
    {
      char ret = data[size-1];
      data[size] = 0;
      size--;
      return ret;
    }
  else
    {
      //handle error right?
      cerr << "nothing left in stack" << endl;
    }
}

char Stack::top()
{
  if(size > 0)
    return data[size-1];
  //cout error
  cerr << "nothing left in stack" << endl;
}

bool Stack::isEmpty()
{
  return size < 1;
}

Stack::~Stack()
{
  delete [] data;
}

//main function
int main()
{
	
  std::string stringVar;
  while(cin >> stringVar)
    {
      Stack s;
      for(unsigned i = 0; i < stringVar.size(); i++)
	{
	  s.push(stringVar[i]);
	}

      while(!s.isEmpty())
	{
	  cout << s.pop();
	}
      cout << endl;
    }
  
  return 0;
}
