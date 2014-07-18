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


//abstract base class
Ship::Ship(int speed, int tonnage, int turnSpeed, int maxHull, int maxShield, int maxArmor) : 
  speed(speed), tonnage(tonnage), turnSpeed(turnSpeed), maxHull(maxHull), maxShield(maxShield), maxArmor(maxArmor),
  hull(maxHull), shield(maxShield), armor(maxArmor)
{
  
}

Ship::~Ship()
{
}

std::string Ship::getShipType() const
{
  return "Ship";
}

//Protected Function
int Ship::getHullDiff() const
{
  return maxHull - hull;
}

int Ship::getShieldDiff() const
{
  return maxShield - shield;
}

int Ship::getArmorDiff() const
{
  return maxArmor - armor;
}

double Ship::getDamageRating() const
{
  //shields dont count
  return (getHullDiff() + getArmorDiff())/3; 
}
