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

template<class Element>
Matrix<Element>::Matrix(int newRows, int newCols) 
  : rows(newRows), cols(newCols), m(newRows)
						    
{
  //fill the matrix
  for(int i = 0; i < rows; i++)
    {
      m[i] = new Array<Element>(cols);
    }
}

template<class Element>
Matrix<Element>::~Matrix()
{
  //destructor delete everything we new'd
  for(int i = 0; i < rows; i++)
    {
      delete m[i];
    }
}

template<class Element>
int Matrix<Element>::numRows()
{
  return rows;
}

template<class Element>
int Matrix<Element>::numCols()
{
  return cols;
}

template<class Element>
Array<Element> & Matrix<Element>::operator[](int row)
{
  if(!(row >=0 && row < rows))
    throw IndexOutOfBoundsException();
  return *m[row];
}

template<class Element>
void Matrix<Element>::print(std::ostream & out)
{
  for(int i = 0; i < rows; i++)
    {
      out << *m[i] << std::endl;
    }
}

template<class T>
std::ostream& operator<< (std::ostream &out, Matrix<T> &m)
{
  m.print(out);
  return out;
}
