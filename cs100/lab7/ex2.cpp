//ben quach and rachel law
#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

int main()
{
  stack<char, vector<char> > st;
  string input;
  cin >> input;
  for(unsigned i = 0 ; i < input.size(); i++)
    {
      st.push(input[i]);
    }
  while(!st.empty())
    {
      
      cout << st.top();
      st.pop();
    }
  return 0;
}
