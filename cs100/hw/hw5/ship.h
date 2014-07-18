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

#ifndef _SHIP_H_
#define _SHIP_H_

#include <vector>
#include <string>
#include <cmath>

//pure virt class
class Ship
{
 public:
  Ship(int speed, int tonnage, int turnSpeed, int maxHull, int maxShield, int maxArmor);
  virtual ~Ship();
  //combat readiness function
  //the higher the value, the quicker the ship
  //can reenter battle
  virtual double combatReadiness() = 0;

  virtual std::string getShipType() const;
 protected:
  int getHullDiff() const;
  int getShieldDiff() const;
  int getArmorDiff() const;
  double getDamageRating() const;
  int tonnage;
  int speed;
  int turnSpeed;
  int hull, shield, armor;
  int maxHull, maxShield, maxArmor;
  
};

#endif
