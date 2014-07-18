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

#ifndef _DREADNOUGHT_H_
#define _DREADNOUGHT_H_

#include "ship.h"

//Dreadnought is a ship that
//has its combat readiness influenced by its
//turrets and firing arcs
class Dreadnought : public Ship
{
 public:
  Dreadnought();
  ~Dreadnought();
  virtual double combatReadiness();
  virtual std::string getShipType() const;
 protected:
  std::vector<int> firingArcs;
};

#endif
