//ben quach and rachel law
#include <iostream>
#include <map>

using namespace std;

class phonebook
{
public:
  map<string, string> m;
  void add(string name, string num)
  {
    m.insert(pair<string,string>(name, num));
  }
  void remove(string name)
  {
    m.erase(name);
  }
  string find(string name)
  {
    //ret phone num
    return m.find(name)->second;
    
  }
  void print()
  {
    for(map<string,string>::iterator i = m.begin(); i != m.end(); i++)
      {
	cout << "NAEM: " << i->first << " NUMBA : " << i->second << endl;
      }
  }
};

int main()
{
  phonebook b;
  cout << "ADDED ALEJANDRO" << endl;
  b.add("alejandro", "714-580-3649");
  b.print();
  cout << "ADDED ALBERTO" << endl;
  b.add("alberto", "714-421-1252");
  b.print();
  cout << "FIND ALBERTO" << endl;
  cout << b.find("alberto") << endl;
  b.print();
  cout << "REMOVED ALEJANDRO" << endl;
  b.remove("alejandro");
  b.print();
  return 0;
}
