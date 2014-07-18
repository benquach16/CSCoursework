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

#ifndef _FRIGATE_H_
#define _FRIGATE_H_

#include "ship.h"

//Frigate is a scout ship
//Combat readiness is influenced by speed and radar
class Frigate : public Ship
{
 public:
  Frigate();
  //functions to overwrite
  virtual ~Frigate();
  virtual double combatReadiness();
  virtual std::string getShipType() const;
 protected:
  int scannerArc;
};


#endif
