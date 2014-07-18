/*
 * Course: CS 100 Fall 2013
 *
 * First Name: Benjamin
 * Last Name: Quach
 * Username: bquac002
 * email address: bquac002@ucr.edu
 *
 *
 * Assignment: hw3
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA. */

#include <iostream>
#include "String.h"

using namespace std;

int main()
{
  String str("abcd");
  String str2("abcde");

  cout << str << endl;
  cout << str2 << endl;
  cout << str.size() <<endl;
  cout << str2.size() << endl;
  String str3(str2);
  cout << str3 << endl;

  str3 = "hijklm";
  cout << str3 << endl;

  cout << str2.indexOf('b') << endl;
  cout << str.indexOf('Z') << endl;

  cout << str2.indexOf(str) << endl;
  cout << str2.indexOf(str2) << endl;
  cout << str2.indexOf("cde") << endl;
  
  if(str == str2)
    cout << "str == str2" << endl;
  if(str != str2)
    cout << "str != str2" << endl;
  if(str3 > str)
    cout << "str3 > str" << endl;
  if(str <= str2)
    cout << "str <= str2" << endl;
  cout << str + str2 << endl;
  
  str2 += "fghijkl";
  cout << str2 << endl;
  
  cout << "input: "<<endl;
  cout << flush;
  String str4;
  cin >> str4;
  cout <<str4<<endl;
  return 0;
}
