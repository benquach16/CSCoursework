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

#ifndef _STACK_H_
#define _STACK_H_

#define STACK_CAPACITY 1000

class Stack
{
	public:
	Stack();
	
	void push( char c );
	char pop();
	char top();
	
	bool isEmpty();
	
	~Stack();
	
	private:
	char *data;
	int size;
};

#endif
