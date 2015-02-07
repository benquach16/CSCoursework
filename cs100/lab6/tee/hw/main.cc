#include "Coins.h"

const int CENTS_FOR_CANDYBAR = 482;

int main()
{
  Coins pocket(100, 10, 10, 100);
  std::cout << "I started with " << pocket << " in my pocket" << std::endl;
  Coins payForCandy = pocket.extractChange(CENTS_FOR_CANDYBAR);
  std::cout << "I bought a candy bar for " << CENTS_FOR_CANDYBAR << " cents using "
	    << payForCandy << std::endl;
  std::cout << "I have " << pocket << " left in my pocket" << std::endl;
  return 0;
}
