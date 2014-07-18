/*
* Course: CS 100 Fall 2013
*
* First Name: Ben
* Last Name: Quach
* Username: bquac002
* email address: bquac002@ucr.edu
*
*
* Assignment: hw2
*
* I hereby certify that the contents of this file represent
* my own original individual work. Nowhere herein is there
* code from any outside resources such as another individual,
* a website, or publishings unless specifically designated as
* permissible by the instructor or TA. */
// Coins.h ///  The name of this file.


#include <iostream>

const int CENTS_PER_QUARTER = 25, CENTS_PER_DIME = 10, CENTS_PER_NICKEL = 5;


class Coins
  {
  public:
    Coins( int q, int d, int n, int p );
    void depositChange( Coins c );
    bool hasSufficientAmount( int amount );
    Coins extractChange( int amount );
    void print( std::ostream& out );
  private:
    //function to convert change automatically
    void normalize();
    int quarters, dimes, nickels, pennies;
  };

std::ostream & operator<< ( std::ostream & out, Coins & c );

