/*
 * Course: CS 100 Fall 2013
 *
 * First Name: Benjamin
 * Last Name: Quach
 * Username: bquac002
 * email address: bquac002@ucr.edu
 *
 *
 * Assignment: hw4
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
  String str1("abcd");
  cout << str1 << endl;
  cout << "length : " << str1.length() << endl;
  cout << "str1[0] == "<< str1[0] << endl;
  cout << "str1[3] == " << str1[3] << endl;
  String str2("efghijkl");
  cout << str2 << endl;
  cout << "length : " << str2.length() << endl;
  str2 = str1;
  cout << str1 << endl;
  cout << str2 + str1 << endl;
  String str3("testString");
  String str5("abdc");
  if(str1 == str2)
    cout << "str1 == str2 " << endl;
  if(str1 == str3)
    cout << "str1 == str3 " << endl;
  if(str1 == str5)
    cout << "str1 == str5" << endl;
  str1 += str3;
  cout << str1 << endl;
  if(str1 == str3)
    cout << "str1 == str3 " << endl;
  String str4;
  cin >> str4;
  cout <<str4 << endl;
  return 0;
}
