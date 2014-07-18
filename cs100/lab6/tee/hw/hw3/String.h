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

#ifndef _STRING_H_
#define _STRING_H_

#include <iostream>

static int cstrlen( const char* buf );
static char* concat( char* dest, char *source );

class String
{
 public:
  String( const char * s = "" );
  String( const String & s); //copy constructor
  String& operator= ( const String & s );

  char& operator[] ( int index );
  int size();
  String reverse();
  int indexOf( int c );
  int indexOf( String pattern );
  bool operator==( String s );
  bool operator!=( String s );
  bool operator>( String s );
  bool operator<( String s );
  bool operator>=( String s );
  bool operator<=( String s );
  String operator+( String s );
  String operator+=( String s );
  void print( std::ostream & out );
  void read( std::istream & in );
  ~String();
 private:
  bool inBounds( int i )
  {
    return i>=0 && i < len;
  }
  char * buf;
  int len;
};

std::ostream & operator<< (std::ostream & out, String str);
std::istream & operator>> (std::istream & in, String & str);

#endif
