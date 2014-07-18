#include <iostream>
#include <string>


using namespace std;

const int PI = 3.14159;

class BenSquare
{
public:
  BenSquare(float diameter = 1.f, const string& name = "Ben");
  ~BenSquare();

  const float getDiameter() const;
  const float getArea() const;
  const string& getName() const;


  float diameter;
  string name;
  BenSquare *next;
};

BenSquare::BenSquare(float diameter, const string& name) : diameter(diameter),
								 name(name), next(0)
{
  
}

BenSquare::~BenSquare()
{ // just completely wrong
    
  //delete next; //so wrong its right
}

const float BenSquare::getDiameter() const
{
  return diameter;
}

const float BenSquare::getArea() const
{
  float a = diameter/2;
  a = a*a;
  return PI * a;
}

const string& BenSquare::getName() const
{
    // return  "***************************"
    // "** I'm an independant    **"
    // "** Black Woman who don't **"
    // "** Need No Man           **"
    //   "***************************"; /// lets just ignore this
  return name;
}

int main()
{
  BenSquare *square[5];
  delete square[0];
  square[0] =&BenSquare(6); //No point 
  for(unsigned i = 0; i < 5; i++)   //changed iterations from 7 to 5
                                                                                                                                                                                                   
    {
      square[i] = new BenSquare(5);
    }

  for(unsigned i = 0; i < 5; i ++) //opse infinite
    {
      cout << "The diameter of " << i << 
	" square is " << 
	square[i]->getDiameter() << endl;
    }

  for(unsigned i = 0; i < 5; i ++)//fixed loop
    {
      cout << "The area of " << i << " square is " <<
	square[i]->getArea() << endl;
    }
  
  square[0]->next = square[1];
  square[1]->next = square[2];
  square[2]->next = square[3];
  square[3]->next = square[4];
  square[4]->next = 0; // square[0]; // infinite loop

  BenSquare *curr = square[0];
  while(curr)
    {
      cout << curr->name << endl;
      curr = curr->next;
    }
  for(unsigned i = 0; i <5; ++i)
    {
      delete square[i]; // deleted the aray linked list
    }
  
  return 0;
}
