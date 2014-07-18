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

#include <iostream>
#include "dreadnought.h"

const int TONNAGE = 7000;
const int SPEED = 20;
const int MAXTURN = 20;
const int MAXHULL = 6000;
const int MAXSHIELD = 6000;
const int MAXARMOR = 10000;
const int MAXTURRETS = 4;

Dreadnought::Dreadnought() : 
  Ship(TONNAGE, SPEED, MAXTURN, MAXHULL, MAXSHIELD, MAXARMOR)
{
  //create cr influences
  for(int i = 0; i < MAXTURRETS; i++)
    {
      int n = rand()%3+1;
      switch(n)
	{
	case 1:
	  {
	    firingArcs.push_back(90);
	    break;
	  }
	case 2:
	  {
	    firingArcs.push_back(180);
	    break;
	  }
	case 3:
	  {
	    firingArcs.push_back(270);
	    break;
	  }
	}
    }
  shield -= rand()%2000;
  armor-=rand()%1000;
}

Dreadnought::~Dreadnought()
{
  
}

double Dreadnought::combatReadiness()
{
  //calc CR
  std::cout << getShipType() << " combat readiness" << std::endl;
  double CR = 0;
  CR += speed/10;
  CR += sqrt(turnSpeed);
  //get the firing arcs
  for(unsigned i = 0; i < firingArcs.size(); i++)
    {
      CR+=firingArcs[i]*2;
    }
  CR/=getDamageRating()+1;
  std::cout << CR << std::endl;
  return CR;
}

std::string Dreadnought::getShipType() const
{
  return "Dreadnought";
}
