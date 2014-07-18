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


#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <iostream>


//include the exception handling here so matrix and this can access it
class IndexOutOfBoundsException{};

template<typename T>
class Array
{
 private:
  int len;
  T * buf;
 public:

  Array<T>( int newLen );

  Array<T>( Array<T> & l );
  ~Array();
  int length();

  T & operator [] ( int i );
  void print( std::ostream & out );
  template<typename T2>
  friend std::ostream & operator << ( std::ostream & out, Array<T2> & a);
};

#include "Array.cpp"

#endif
