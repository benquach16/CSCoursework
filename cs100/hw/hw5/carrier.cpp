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
#include "carrier.h"

const int TONNAGE = 4500;
const int SPEED = 50;
const int MAXTURN = 40;
const int MAXHULL = 2000;
const int MAXSHIELD = 3000;
const int MAXARMOR = 2000;
const int MAXFIGHTERS = 10;

Carrier::Carrier() :
  Ship(TONNAGE, SPEED, MAXTURN, MAXHULL, MAXSHIELD, MAXARMOR)
{
  for(int i = 0; i < MAXFIGHTERS; i++)
    {
      fighters.push_back(rand()%100+1);
    }
  shield-=rand()%1000;
  armor-=rand()%1000;
}

Carrier::~Carrier()
{
}

double Carrier::combatReadiness()
{
  //calculate readiness of a carrier
  std::cout << getShipType() << " combat readiness"<< std::endl;
  double CR = 0;
  CR += speed/5;
  CR += sqrt(turnSpeed);
  
  int total = 0;
  //take into account number of fighters
  std:: cout << "Fighter Bay : " << std::endl;
  for(unsigned i = 0; i < fighters.size(); i++)
    {
      total += fighters[i];
      std::cout << "    Fighter " << i << " " << fighters[i] << std::endl; 
    }
  total/=10;
  CR+= total;
  CR/=getDamageRating()+1;
  std::cout << CR << std::endl;
  return CR;
}

std::string Carrier::getShipType() const
{
  return "Carrier";
}
