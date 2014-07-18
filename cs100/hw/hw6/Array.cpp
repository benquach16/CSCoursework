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

#include <assert.h>
#include <iomanip>

template<typename T>
Array<T>::Array(int newLen) : len(newLen), buf(new T[newLen])
{
  
}
template<typename T>
Array<T>::Array(Array<T> & l) : len(l.len), buf(new T[l.len])
{
  for(int i = 0; i < l.len; i++)
    {
      buf[i] = l.buf[i];
    }
}

template<typename T>
Array<T>::~Array()
{
  delete [] buf;
}

template<typename T>
int Array<T>::length()
{
  return len;
}

template<typename T>
T & Array<T>::operator[]( int i )
{
  //throw exception here
  if(!(i >= 0 && i < len))
    {
      throw IndexOutOfBoundsException();
    }
  return buf[i];
}

template<typename T>
void Array<T>::print(std::ostream& out)
{
  for(int i = 0; i < len; i++)
    out << std::setw(5) << buf[i];
}

template<typename T>
std::ostream& operator<< ( std::ostream & out , Array<T> & a )
{
  a.print(out);
  return out;
}
