/*
 * Course: CS 100 Fall 2013
 *
 * First Name: Benjamin
 * Last Name: Quach
 * Username: bquac002
 * email address: bquac002@ucr.edu
 *
 *
 * Assignment: hw7
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA. */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

using namespace std;

//basic function, reads in words from file and adds them to the set
void readExcludedWords(char *filename, set<string> &s)
{
  ifstream file(filename);
  string input;
  while(file >> input)
    {
      s.insert(input);
    }
}

void print(set<string> &s, map<string, int> &m)
{

  //otuput to make sure everythign is correct
  for(map<string,int>::iterator i = m.begin(); i != m.end(); i++)
    {
      cout << i->first<< " " << i->second << endl;
    }
  cout << "excluded words" << endl;
  for(set<string>::iterator i = s.begin(); i != s.end(); i++)
    {
      cout << (*i) << endl;
    }
}

int main()
{
  set<string> s;
  map<string, int> m;
  readExcludedWords("excludedWords.txt", s);
  
  //now read from input file
  ifstream file("input.txt");
  string input;
  while(file >> input)
    {
      if(s.find(input) == s.end())
	{
	  //did not find in the set so we can add it to the map

	  map<string,int>::iterator i = m.find(input);
	  if(i != m.end())
	    {
	      i->second++;
	    }
	  else
	    {
	      m.insert(pair<string,int>(input, 1));
	    }
	  
	}
    }
  print(s, m);

  return 0;
}
