#include <iostream>
#include "String.h"

using namespace std;

int main()
{
  String str1("abcd");
  cout << str1 << endl;
  cout << "length : " << str1.length() << endl;
  cout << "str1[0] == "<< str1[0] << endl;
  String str2("efghijkl");
  cout << str2 << endl;
  str2 = str1;
  cout << str1 << endl;
  cout << str2 + str1 << endl;
  String str3("testString");
  if(str1 == str2)
    cout << "str1 == str2 " << endl;
  if(str1 == str3)
    cout << "str1 == str3 " << endl;
  str1 += str3;
  cout << str1 << endl;
  if(str1 == str3)
    cout << "str1 == str3 " << endl;
  String str4;
  cin >> str4;
  cout <<str4 << endl;
  return 0;
}
