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

#ifndef _CARRIER_H_
#define _CARRIER_H_

#include "ship.h"

//A carrier is a type of ship that
//has its combat readiness based on the
//health of its fighters
class Carrier : public Ship
{
 public:
  Carrier();
  ~Carrier();

  virtual double combatReadiness();
  virtual std::string getShipType() const;
 protected:
  std::vector<int> fighters;
};

#endif
