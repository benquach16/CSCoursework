//ben quach and rachel law
#include <iostream>
#include <vector>

using namespace std;

void print(vector<int> t, string msg)
{
  cout << msg<<endl;
  for(vector<int>::iterator i = t.begin(); i != t.end(); i++)
    {
      cout << (*i) << endl;
    }
}

int main()
{
  vector<int> t;
  vector<int> t2;
  for(unsigned i = 0; i < 5; i++)
    t.insert(t.begin(), i);
  print(t, "THIS IS A VECTOR T");
  for(unsigned i = 40; i < 45; i++)
    {
      t2.insert(t2.begin(), i);
    }

  print(t2, "T2 VETOR");
  t.swap(t2);

  print(t, "T SWAP WTH T2");
  t.insert(t.begin(), 5);

  print(t, "T INERT");
  t.erase(t.begin());

  print(t, "T ERASE");
  t2.clear();

  print(t, "THIS IS A VECTOR T2");
  return 0;
}
