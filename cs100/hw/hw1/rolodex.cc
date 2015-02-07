/*

* Course: CS 100 Fall 2013

*

* First Name: Benjamin
* 
* Last Name: Quach

* Username: bquac002

* email address: bquac002@ucr.edu

*

*

* Assignment: hw1
*

* I hereby certify that the contents of this file represent

* my own original individual work. Nowhere herein is there

* code from any outside resources such as another individual,

* a website, or publishings unless specifically designated as

* permissible by the instructor or TA.

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct node

{
  string firstName, lastName;
  string address;
  string phoneNum;
  node *next;
  //constructor for node
  node(const string& firstName, const string& lastName,
       const string& address, const string& phoneNum) : 
    firstName(firstName), lastName(lastName), address(address),
    phoneNum(phoneNum), next(0)
  {
  }
};

//rolodex is a node in a linked list
class Rolodex
{
 public:
  Rolodex();
  ~Rolodex();

  //function to add another rolodex onto the list
  void push(const string& firstName, const string& lastName,
	    const string& address, const string& phoneNum);
  //function to erase a rolodex from the list
  void erase(const string& lastName);

  //print function
  void print();

  //get function
  void get(const string& lastName);

  //save function
  void save(const string& filename);
  //load function
  void load(const string& filename);

  //empty the entire list
  void clear();
 private:
  node *head;
};

//global helper function
string toLower(const string& str)
{
  string ret(str);
  for(unsigned i = 0; i < ret.length(); i ++)
    {
      ret[i] = tolower(ret[i]);
    }
  return ret;
}

Rolodex::Rolodex() : head(0)
{
}

Rolodex::~Rolodex()
{
  //deallocate memory
  node *currentNode = head;
  while(currentNode)
    {
      node *next = currentNode->next;
      delete currentNode;
      currentNode = next;
    }
}

void Rolodex::push(const string& firstName, const string& lastName, const string& address,
		   const string& phoneNum)
{
  node *newNode = new node(firstName, lastName, address, phoneNum);
  //trigger edge cases
  if(!head)
  {
    //make this the head
    head = newNode;
    return;
  }
  //case where we replace head
  if(toLower(head->lastName) >= toLower(newNode->lastName))
    {
      newNode->next = head;
      
      head = newNode;
      return;
    }



  //if not lets loop!!
  node* currentNode = head;
  //lets save the previous node for insertion
  node* lastNode = head;
  while(currentNode->next)
    {
      if(toLower(currentNode->next->lastName) >= toLower(newNode->lastName))
	{

	  newNode->next  = currentNode->next;
	  currentNode->next = newNode;
	  
	  return;
	}

      currentNode = currentNode->next;
    }
  //add to the end

  if(currentNode->next)
    {
      node *tmp = currentNode->next->next;
      newNode->next = tmp;
    }

  currentNode->next = newNode;
 
}

void Rolodex::erase(const string& lastName)
{
  //check edge cases first
  if(head->lastName == lastName)
    {

      node *tmp = head->next;
      delete head;
      head = tmp;
      return;
    }
  
  node *currentNode = head;
  while(currentNode->next)
    {

      //while has a next
      if(currentNode->next->lastName == lastName)
	{
	  //found it

	  node *tmp = currentNode->next->next;
	  delete currentNode->next;
	  currentNode->next = tmp;
	  return;

	}
      currentNode = currentNode->next;
    }
  cout << "Not Found" << endl;
}

void Rolodex::print()
{
  node* currentNode = head;
  while(currentNode)
    {
      cout << currentNode->lastName << "," << currentNode->firstName << endl;
      cout << "Address: " << currentNode->address << endl;
      cout << "Phone Number: " << currentNode->phoneNum << endl;
      cout << endl;
      currentNode = currentNode->next;
    }
}

void Rolodex::get(const string& lastName)
{
  //lets find the address!
  node *currentNode = head;
  while(currentNode)
    {
      if(currentNode->lastName == lastName)
	{
	  //print out
	  cout << currentNode->lastName << "," << currentNode->firstName << endl;
	  cout << "Address: " << currentNode->address << endl;
	  cout << "Phone Number: " << currentNode->phoneNum << endl;
	  cout << endl;

	  return;
	}
      currentNode = currentNode->next;
    }
  //did not find anything
  cout << "Could not find information about this person" << endl;
}

void Rolodex::save(const string& filename)
{
  //save to a filename
  ofstream file(filename.c_str());

  //loop
  node *currentNode = head;
  while(currentNode)
    {
      //follow this format, it'll be easier
      file << currentNode->lastName << endl;
      file << currentNode->firstName << endl;
      file << currentNode->address << endl;
      file << currentNode->phoneNum << endl;

      currentNode = currentNode->next;

    }

}


void Rolodex::load(const string& filename)
{
  //load a file
  ifstream file(filename.c_str());
  if(!file)
    {
      cout << "Failed to read from file" << endl;
      return;
    }
  //we are loading a new file
  clear();

  //read from this file
  string lastname;
  string firstname;
  string address;
  string phonenum;

  while(getline(file, lastname))
    {

      //getline 3 more times
      getline(file, firstname);
      getline(file, address);
      getline(file, phonenum);

      push(firstname, lastname, address, phonenum);
    }
}

void Rolodex::clear()
{
  //deallocate memory
  node *currentNode = head;
  while(currentNode)
    {
      node *next = currentNode->next;
      delete currentNode;
      currentNode = next;
    }
  head = 0;
}


int main()
{
  char input;

  bool quit = false;
  bool modified = false;
	
  Rolodex r;
	
  while(!quit)
    {
      //output commands
      cout << "i - insert new address " << endl;
      cout << "f - find address " << endl;
      cout << "d - delete address " << endl;
      cout << "p - print rolodex " << endl;
      cout << "l - load rolodex from file " << endl;
      cout << "s - save rolodex from file " << endl;
      cout << "q - quit " << endl;
      cin >> input;
      cin.ignore();
      switch(input)
	{
	case 'i':
	  {
	    //insert an address into the rolodex
	    string firstName, lastName;
	    string address;
	    string phoneNum;
	    cout << "Enter first name: " << endl;
	    getline(cin, firstName);
	    cout << "Enter last name: " << endl;
	    getline(cin, lastName);
	    cout << "Enter address: " << endl;
	    getline(cin, address);
	    cout << "Enter phone number: " << endl;
	    getline(cin, phoneNum);
	    r.push(firstName, lastName, address, phoneNum);
	    modified = true;
	    break;
	  }
	case 'f':
	  {
	    //find an address
	    string lastName;
	    cout << "Enter last name: " << endl;
	    getline(cin, lastName);
	    r.get(lastName);
	    break;
	  }
	case 'd':
	  {
	    //delete an address
	    string lastName;
	    cout << "Enter last name to delete: "<< endl;
	    getline(cin, lastName);
	    r.erase(lastName);
	    modified = true;
	    break;
	  }
	case 'p':
	  {
	    //print out the rolodex
	    r.print();
	    break;
	  }
	case 'l':
	  {
	    //load a file!!
	    string filename;
	    cout << "Enter filename: "<<endl;
	    getline(cin, filename);
	    r.load(filename);
	    modified = false;
	    break;
	  }
	case 's':
	  {
	    //save a file!
	    modified = false;
	    string filename;
	    cout << "Enter filename: " << endl;
	    getline(cin, filename);
	    r.save(filename);
	    break;
	  }
	case 'q':
	  {
	    //quit program
	    if(modified)
	      {
		//its modified so we check if the user wants to save
		string decision;
		cout << "File as been modified, do you wish to save? (y/n)" << endl;
		getline(cin, decision);
		if(decision == "y")
		  {
		    //save
		    string filename;
		    cout << "Enter filename: " << endl;
		    getline(cin, filename);
		    r.save(filename);
		  }
		
	      }
	    quit = true;
	    break;
	  }
	}
    }
}
