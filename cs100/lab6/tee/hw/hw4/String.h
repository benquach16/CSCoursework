#ifndef _STRING_H_
#define _STRING_H_

#include <iostream>

class String
{
 public:
  String(const char* s = "");
  String(const String & s);
  String operator=(const String & s);
  char & operator[](const int index);
  int length() const;
  int indexOf(char c) const;
  bool operator==(const String &s) const;
  ///concatenates this and s
  String operator+(const String &s) const;
  ///concatenates s onto end of this
  String operator+=(const String &s);
  void print(std::ostream & out);
  void read(std::istream & in);

  ~String();
 private:
  bool inBounds( int i )
  {
    return i >= 0 && i < length();
  }
  struct ListNode
  {
    char info;
    ListNode *next;
    ListNode(char newNode, ListNode *newNext) 
      : info(newNode), next(newNext)
    {
      
    }
    //you may add static methods here
  };
  ListNode *head;
};
std::ostream & operator << ( std::ostream &out ,String str);
std::istream & operator >> ( std::istream &in, String &str);
#endif
