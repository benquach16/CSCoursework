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


#include "Array.h"
#include "Matrix.h"

#include <iostream>
using namespace std;

//required function
template <typename T>
void fillMatrix(Matrix<T> &m)
{
  int i, j;

  for(i = 0; i < m.numRows(); i++)
    {
      m[i][0] = T();
    }
  for(j = 0; i < m.numCols(); i++)
    {
      m[0][j] = T();
    }
  for(i = 1 ; i < m.numRows(); i++)
    {
      for(j = 1; j < m.numCols(); j++)
	{
	  m[i][j] = T(i*j);
	}
    }
   
}


int main()
{
  Matrix<int> m(10,5);
  fillMatrix(m);
  cout << m;
  Matrix<double> M(8, 10);
  fillMatrix(M);
  cout << M;
  //throw an exception here
  try
    {
      //test exception from matrix
      M[50][5] = 5;
    }
  catch(IndexOutOfBoundsException)
    {
      cerr << "Caught an index out of bounds exception" << endl;
    }

  return 0;
}
