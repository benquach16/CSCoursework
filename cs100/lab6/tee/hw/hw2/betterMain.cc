/*
* Course: CS 100 Fall 2013
*
* First Name: Ben
* Last Name: Quach
* Username: bquac002
* email address: bquac002@ucr.edu
*
*
* Assignment: hw2
*
* I hereby certify that the contents of this file represent
* my own original individual work. Nowhere herein is there
* code from any outside resources such as another individual,
* a website, or publishings unless specifically designated as
* permissible by the instructor or TA. */

#include "Coins.h"

int main()
{
  //create objecst
  Coins pocket(5, 3, 6, 8);
  Coins piggyBank(50,50,50,50);
  std::cout << "I have " << pocket << "in my pocket and " << 
    piggyBank << " in my piggy bank" << std::endl;
  Coins chips = pocket.extractChange(68);
  std::cout << "I purchased a bag of chips for " << chips << std::endl;
  std::cout << "I have " << pocket << " left in my pocket" << std::endl;

  Coins found = piggyBank.extractChange(100);
  pocket.depositChange(found);

  std::cout << "I take " << found << " from my piggybank" << std::endl;
  std::cout << "I have " << pocket << " in my pocket" << std::endl;

  
  std::cout << "I find 54 cents in the couch" << std::endl;
  piggyBank.depositChange(Coins(2,0,0,2));
  std::cout << "I now have " << piggyBank << " in my piggy bank" << std::endl;
  

  return 0;
}
