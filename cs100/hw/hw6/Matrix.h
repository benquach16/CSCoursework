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

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Array.h"

template <class Element>
class Matrix
{
 private:
  int rows, cols;
  Array <Array<Element>* > m;
 public:
  Matrix<Element>(int newRows, int newCols);
  ~Matrix<Element>();
  int numRows();
  int numCols();

  Array < Element > & operator[]( int row );
  
  void print(std::ostream & out);
  template<class T>
  friend std::ostream& operator<< (std::ostream &out, Matrix<T> &m);
};

#include "Matrix.cpp"

#endif
