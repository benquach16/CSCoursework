/*
 * Course: CS 100 Fall 2013
 *
 * First Name: Benjamin
 * Last Name: Quach
 * Username: bquac002
 * email address: bquac002@ucr.edu
 *
 *
 * Assignment: hw7
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA. */

#include <iostream>
#include <set>
#include <fstream>

using namespace std;

//loads input into a multiset
void sort(multiset<int> &s)
{
  int i;
  while(cin >> i)
    {
      s.insert(i);
    }
}

int main()
{
  //sets sort for us
  multiset<int> s;
  sort(s);
  ofstream outEvens("evens.txt");
  ofstream outOdds("odds.txt");
  for(set<int>::iterator i = s.begin(); i != s.end(); i++)
    {
      cout << *i << " ";
      //evens get their own line but odds are seperated by space
      //arbitrary
      if((*i)%2==0)
	outEvens << *i << endl;
      else
	outOdds << *i << " ";
    }
  
  return 0;
}
