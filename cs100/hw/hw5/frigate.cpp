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
#include "frigate.h"

const int TONNAGE = 2000;
const int SPEED = 120;
const int MAXTURN = 100;
const int MAXHULL = 1000;
const int MAXSHIELD = 1000;
const int MAXARMOR = 1000;
const int SCANNERARC = 360;

Frigate::Frigate() : 
  Ship(TONNAGE, SPEED, MAXTURN, MAXHULL, MAXSHIELD, MAXARMOR), scannerArc(SCANNERARC)
{
  //damage the ship arbitarily so we can see the effects on CR
  shield-=rand()%100;
  armor-= rand()%200;
  hull-=rand()%200;
}

Frigate::~Frigate()
{
  
}

double Frigate::combatReadiness()
{
  //calculate the combat readiness of a frigate
  //not affected by weapons fighters and full bonus from speed

  std::cout << getShipType() << " combat readiness" << std::endl;
  double CR = 0;
  CR += speed;
  CR += turnSpeed;
  
  //accoutn for damage
  int effectiveScannerArc = scannerArc;
  effectiveScannerArc/=(int)getDamageRating()+1;
  CR += effectiveScannerArc*0.5;

  CR /= getDamageRating()+1;
  std::cout << "Effective Scanner Range: " << effectiveScannerArc << std::endl;
  std::cout << CR << std::endl;
  return CR;
}

std::string Frigate::getShipType() const
{
  return "Frigate";
}
