#include "String.h"

String::String(const char * s) : head(0)
{
  //get size and add as nodes
  ListNode *currentNode = head;
  for(unsigned i = 0; s[i] != '\0'; i++)
    {
      if(!currentNode)
	{
	  currentNode = new ListNode(s[i], 0);
	  if(!head)
	    head = currentNode;
	}
      else
	{
	  currentNode->next = new ListNode(s[i], 0);
	  currentNode = currentNode->next;
	}
    }
}

String::String(const String & s) : head(0)
{
  //make sure that we set heads so we can iterate later
  
  ListNode *currentIt = s.head;
  ListNode *currentNode = head;
  while(currentIt)
    {
      if(!currentNode)
	{
	  currentNode = new ListNode(currentIt->info,0);
	  if(!head)
	    head = currentNode;
	}
      else
	{
	  currentNode->next = new ListNode(currentIt->info, 0);
	  currentNode = currentNode->next;
	}
      currentIt = currentIt->next;
    }
}

String String::operator=(const String & s)
{
  //clear this
  
  ListNode *currentNode = this->head;
  while(currentNode)
    {
      ListNode *t = currentNode->next;
      delete currentNode;
      currentNode = t;
    }
  head = 0;
  
  
  ListNode *currentIt = s.head;
  currentNode = head;
  while(currentIt)
    {
      if(!currentNode)
	{
	  currentNode = new ListNode(currentIt->info,0);
	  if(!head)
	    head = currentNode;
	}
      else
	{
	  currentNode->next = new ListNode(currentIt->info, 0);
	  currentNode = currentNode->next;
	}
      currentIt = currentIt->next;
    }
  return *this;
}

char & String::operator[](const int index)
{
  //go thru the list
  ListNode *currentNode = head;
  int i = index;
  while(currentNode)
    {
      if(!i)
	{
	  return currentNode->info;
	}
      i--;
      currentNode = currentNode->next;
    }
}

int String::indexOf( char c ) const
{
  //similar to subscript operator
  int counter=0;
  ListNode *currentNode = head;
  while(currentNode)
    {
      if(currentNode->info == c)
	{
	  return counter;
	}
      counter++;
      currentNode = currentNode->next;
    }
  return counter;
}

int String::length() const
{
  //count
  int counter = 0;
  ListNode *currentNode = head;
  while(currentNode)
    {
      counter++;
      currentNode = currentNode->next;
    }
  return counter;
}

bool String::operator==(const String & s) const
{
  //loop through both and see if theres any differences
  if(s.length() != length())
     return false;
  ListNode *currentThis = head;
  ListNode *currentS = s.head;
  while(currentThis)
    {
      //go thru all and compare
      if(currentThis->info != currentS->info)
	return false;
      currentThis = currentThis->next;
      currentS = currentS->next;
    }
  return true;
}

String String::operator+(const String &s) const
{
  String ret(*this);
  //append s to the end
  ListNode *currentNode = ret.head;
  while(currentNode->next)
    {
      currentNode = currentNode->next;
    }
  //loop so we get the very end
  ListNode *currentIt = s.head;
  while(currentIt)
    {
      currentNode->next = new ListNode(currentIt->info, 0);
      currentNode = currentNode->next;
      currentIt = currentIt->next;
    }
  return ret;
}

String String::operator+=(const String &s)
{
  //append to end

  //append s to the end
  ListNode *currentNode = head;
  while(currentNode->next)
    {
      currentNode = currentNode->next;
    }
  //loop so we get the very end
  ListNode *currentIt = s.head;
  while(currentIt)
    {
      currentNode->next = new ListNode(currentIt->info, 0);
      currentNode = currentNode->next;
      currentIt = currentIt->next;
    }
  
  return *this;
}

void String::print(std::ostream & out)
{
  
  ListNode *currentNode = head;
  while(currentNode)
    {
      out << currentNode->info;
      currentNode = currentNode->next;
    }
}

void String::read(std::istream & in)
{
  //clear this
  
  ListNode *currentNode = head;
  while(currentNode)
    {
      ListNode *t = currentNode->next;
      delete currentNode;
      currentNode = t;
    }

  head = 0;
  currentNode = head;
  char *input = new char;
  in >> input;
  for(unsigned i = 0; input[i] != '\0'; i++)
    {
      if(!currentNode)
	{
	  currentNode = new ListNode(input[i], 0);
	  if(!head)
	    head = currentNode;
	}
      else
	{
	  currentNode->next = new ListNode(input[i], 0);
	  currentNode = currentNode->next;
	}
    }
}

String::~String()
{
  ListNode *currentNode = head;
  while(currentNode)
    {
      ListNode *t = currentNode->next;
      delete currentNode;
      currentNode = t;
    }
}

std::ostream & operator << ( std::ostream &out, String str)
{
  str.print(out);
  return out;
}

std::istream & operator >> ( std::istream &in, String & str)
{
  str.read(in);
  return in;
}

