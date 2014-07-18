/*
 * Course: CS 100 Fall 2013
 *
 * First Name: Benjamin
 * Last Name: Quach
 * Username: bquac002
 * email address: bquac002@ucr.edu
 *
 *
 * Assignment: hw5
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA. */

#include "ship.h"
#include "frigate.h"
#include "carrier.h"
#include "dreadnought.h"

#include <vector>
#include <iostream>

using namespace std;

void do_shipstuff(vector<Ship*>& allShips)
{
  double totalCR = 0.f;
  for(unsigned i = 0; i < allShips.size(); i++)
    {
      totalCR += allShips[i]->combatReadiness();
    }
  cout << "Total fleet combat rating: " << totalCR << endl;
  double alienCR = rand()%100;

  if(totalCR > alienCR)
    {
      cout << "The fleet is able to defeat the alien fleet" << endl;
    }
  else
    cout << "The fleet is unable to defeat the alien fleet" << endl;
}

int main()
{
  //create pointers to objects
  srand(time(0));
  vector<Ship*> allShips;
  allShips.push_back(new Frigate());
  allShips.push_back(new Carrier());
  allShips.push_back(new Dreadnought());
  do_shipstuff(allShips);
  //delete all
  while(!allShips.empty())
    {
      delete allShips[0];
      allShips.erase(allShips.begin());
    }
  return 0;
}
