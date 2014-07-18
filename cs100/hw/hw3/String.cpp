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

#include "String.h"

int cstrlen( const char * buf )
{
  int counter = 0;
  //make sure we find the endl or null char
  while(buf[counter] != '\0' && buf[counter] != 0)
    {
      //std::cout << (int)buf[counter] << std::endl;
      counter++;
    }
  return counter;
}

char* concat( char *dest, char *source )
{
  //3 for loops?
  int size = cstrlen(dest) + cstrlen(source)+1;
  char tmp[size];
  for(int i = 0; i < cstrlen(dest); i++)
    {
      tmp[i] = dest[i];
    }
  for(int i = (cstrlen(dest)); i < cstrlen(dest) + cstrlen(source); i++)
    {
      tmp[i] = source[i-cstrlen(dest)];
    }
  tmp[size-1] = '\0';
  
  for(unsigned i = 0; i < size; i++)
    {
      dest[i] = tmp[i];
    }
  return dest;
}

String::String( const char * s ) : buf(0), len(0)
{
  //find the length of this char
  len = cstrlen((char*)s);
  buf = new char[len];
  for(unsigned i = 0; i < len ; i ++)
    {
      buf[i] = s[i];
    }
}

String::String( const String & s ) : buf(0), len(s.len)
{
  buf = new char[len];
  for(unsigned i = 0; i < len; i ++)
    {
      buf[i] = s.buf[i];
    }
}

String& String::operator= (const String & s)
{
  //assignment operator
  delete buf;

  len = s.len;
  buf = new char[len+1];
  for(unsigned i = 0; i < len; i++)
    {
      buf[i] = s.buf[i];
    }
  buf[len] = '\0';
  return *this;
}

char& String::operator[] ( int index )
{
  //return lvalue
  return buf[index];
}

int String::size()
{
  return len;
}

String String::reverse()
{
  //for loop this
  String ret(*this);
  for(int i = 0; i < ret.len/2; i++)
    {
      char temp;
      temp = ret.buf[i];
      ret.buf[i] = ret.buf[len-i-1];
      ret.buf[len-i-1] = temp;
    }
  return ret;
}

int String::indexOf( int c )
{
  //for loop this
  for(int i = 0; i < len; i++)
    {
      if( c == buf[i] )
	{
	  return i;
	}
    }

  //return -1
  //because was not found
  return -1;
}

int String::indexOf( String pattern )
{
  //find string in string
  for(int i = 0; i < len; i++)
    {
      //first letter is similar so we loop
      if( pattern[0] == buf[i] && (len-i) >= pattern.len)
	{
	  bool t = true;
	  for(int n = 0; n < pattern.len; n++)
	    {
	      if(pattern[n] != buf[i+n])
		{
		  t = false;
		  break;
		}
	    }
	  if(t)
	    return i;
	}
    }
  return -1;
}

bool String::operator==( String s )
{
  //simple comparisons
  if(s.len != len)
    return false;
  for(int i = 0; i < len; i++)
    {
      if(buf[i] != s[i])
	{
	  return false;
	}
    }
  return true;
}

bool String::operator!=( String s )
{
  //same as above but not
  if(s.len != len)
    return true;  
  for(int i = 0; i < len; i++)
    {
      if(buf[i] != s[i])
	{
	  return true;
	}
    }
  return false;
}

bool String::operator>( String s )
{
  
  int maxSize;
  if(s.len < len)
    maxSize = s.len;
  else
    maxSize = len;
  for(unsigned i = 0; i < maxSize; i++)
    {
      if(buf[i]<=s[i])
	{

	  //std::cout << buf[i] << s[i] << std::endl;
	return false;
	}
    }
  return true;
}

bool String::operator<( String s )
{
  int maxSize;
  if(s.len < len)
    maxSize = s.len;
  else
    maxSize = len;
  for(unsigned i = 0; i < maxSize; i++)
    {
      if(buf[i]>=s[i])
	return false;
    }
  return true;
}

bool String::operator>=( String s )
{
  //modify this later
  int maxSize;
  if(s.len < len)
    maxSize = s.len;
  else
    maxSize = len;
  for(unsigned i = 0; i < maxSize; i++)
    {
      if(buf[i]>s[i])
	return false;
    }
  return true;  
}

bool String::operator<=( String s )
{
  int maxSize;
  if(s.len < len)
    maxSize = s.len;
  else
    maxSize = len;
  for(unsigned i = 0; i < maxSize; i++)
    {
      if(buf[i]<s[i])
	return false;
    }  
  return true;
}

String String::operator+( String s )
{
  //concatenate a new string
  String ret(*this);
  concat(ret.buf, s.buf);
  ret.len = cstrlen(ret.buf);
  return ret;
}

String String::operator+=( String s )
{
  concat(buf, s.buf);
  len = cstrlen(buf);
  return *this;
}

void String::print( std::ostream &out )
{
  out << buf;
}

void String::read( std::istream &in )
{
  delete buf;
  buf = new char;
  in >> buf;
  len = cstrlen(buf);
}

String::~String()
{
  delete buf;
}

//define the << operators
std::ostream& operator << (std::ostream & out, String str )
{
  str.print(out);
  return out;
}

std::istream& operator >> (std::istream & in, String & str)
{
  str.read(in);
  return in;
}
