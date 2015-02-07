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

Coins::Coins(int q, int d, int n, int p) : 
  quarters(q), dimes(d), nickels(n), pennies(p)
{
  
}


void Coins::depositChange(Coins c)
{
  quarters += c.quarters;
  dimes += c.dimes;
  nickels += c.nickels;
  pennies += c.pennies;
  //normalize();
}

bool Coins::hasSufficientAmount(int amount)
{
  //check if we have enough so lets convert this real quick
  Coins tmp(0,0,0,amount);
  tmp.normalize();
  
  if(tmp.quarters > quarters)
      return false;
  else if(tmp.quarters < quarters)
      return true;
  else
    {
      //so quarters are equal
      if(tmp.dimes > dimes)
	return false;
      else if(tmp.dimes < dimes)
	return true;
      else
	{
	  //so dimes and quarters are equal check the rest
	  if(tmp.nickels > nickels)
	    return false;
	  else if(tmp.nickels < nickels)
	    return true;
	  else
	    {
	      //pennies!!
	      if(tmp.pennies > pennies)
		return false;
	      else
		return true;

	    }
	}
    }
}

Coins Coins::extractChange(int amount)
{
  //change int into coints
  
  //ret.normalize();

  //remove ret from *this

  int q=0,d=0,n=0,p=0;
  if(hasSufficientAmount(amount))
    {
      while(amount >= CENTS_PER_QUARTER && q < quarters)
	{
	  amount -= CENTS_PER_QUARTER;
	  q++;
	}
      while(amount >= CENTS_PER_DIME && d < dimes)
	{
	  amount -= CENTS_PER_DIME;
	  d++;
	}
      while(amount >= CENTS_PER_NICKEL && n < nickels)
	{
	  amount -= CENTS_PER_NICKEL;
	  n++;
	}
      while(amount > 0 && p < pennies)
	{
	  amount --;
	  p++;
	}
    }
    
  
  quarters -= q;
  dimes -= d;
  nickels -= n;
  pennies -=p;
    
  Coins ret(q,d,n,p);

  return ret;
}

void Coins::print(ostream& out)
{
  out << quarters << " quarters, " << dimes <<
    " dimes, " << nickels << " nickels, " << pennies << " pennies";
}

//private function
void Coins::normalize()
{
  while(pennies >= CENTS_PER_NICKEL)
    {
      if(pennies >= CENTS_PER_QUARTER)
	{
	  pennies -= CENTS_PER_QUARTER;
	  quarters++;
	}
      else if(pennies >= CENTS_PER_DIME)
	{
	  pennies -= CENTS_PER_DIME;
	  dimes++;
	}
      else
	{
	  pennies-=CENTS_PER_NICKEL;
	  nickels++;
	}
    }
  while(nickels>=(CENTS_PER_DIME/CENTS_PER_NICKEL))
    {
      if(nickels >= (CENTS_PER_QUARTER/CENTS_PER_NICKEL))
	{
	  //convert to quarters
	  nickels-=(CENTS_PER_QUARTER/CENTS_PER_NICKEL);
	  quarters++;
	}
      else
	{
	  nickels-=(CENTS_PER_DIME/CENTS_PER_NICKEL);
	  dimes++;
	}
    }
  
}

ostream &operator << (ostream &out, Coins &c)
{
  c.print(out);
  return out;
}
