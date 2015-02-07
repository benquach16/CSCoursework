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

#include "Coins.h"

using namespace std;


void printMenu()
{
  cout << "a - add change" << endl;
  cout << "r - remove change" << endl;
  cout << "p - print balance" << endl;
  cout << "q - quit" << endl;
}

int main()
{
  Coins myCoins(0,0,0,0);

  bool quit = false;

  //get input
  while(!quit)
    {
      printMenu();
      char input;
      cin >> input;
      switch(input)
	{
	case 'a':
	  {
	    cout << "how many quarters would you like to add?" << endl;
	    int q, d, n, p;
	    cin >> q;
	    cout << "how many dimes would you like to add?" << endl;
	    cin >> d;
	    cout << "how many nickels would you like to add? "<< endl;
	    cin >> n;
	    cout << "how many pennies would you like to add? " << endl;
	    cin >> p;
	    myCoins.depositChange(Coins(q,d,n,p));
	    break;
	  }
	case 'r':
	  {
	    cout << "how much change would you like to remove?" << endl;
	    int change;
	    cin >> change;
	    if(myCoins.hasSufficientAmount(change))
	      {
		Coins c = myCoins.extractChange(change);
		if(!c.hasSufficientAmount(change))
		  {
		    cout << "need more diverse coins" << endl;
		    myCoins.depositChange(c);
		  }

	      }
	    else
	      {
		cout << "not enough coins" << endl;
	      }
	    break;
	  }
	case 'p':
	  {
	    cout << "you have " << myCoins << endl;
	    break;
	  }
	case 'q':
	  {
	    quit = true;
	    break;
	  }
	}
    }
  return 0;
}
