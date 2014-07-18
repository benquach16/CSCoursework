#include<iostream>
#include<vector>
#include<numeric>

using namespace std;

int sum(int a, int b) { return a+b; }
int prod(int a, int b) { return a*b; }
bool forall(bool a, bool b) { return a&&b; }
bool exists(bool a, bool b) { return a||b; }

int main()
{
    vector<int> v;
    vector<bool> b;
    for (int i=1; i<= 10; i++)
    {
	v.push_back(i);
	b.push_back( (i%2==0) ? true : false);
    }

    cout << "v: ["; copy( v.begin(), v.end(),  ostream_iterator<int>(cout, ",") ); cout << "]" << endl;
    cout << "b: ["; copy( b.begin(), b.end(),  ostream_iterator<bool>(cout, ",") ); cout << "]" << endl; 
 
    cout << "Default acc: " << std::accumulate(v.begin(), v.end(), 0) << endl;
    cout << "Sum acc: "     << std::accumulate(v.begin(), v.end(), 0, sum) << endl;
    cout << "Prod acc: "    << std::accumulate(v.begin(), v.end(), 1, prod) << endl;
    cout << "Forall acc: "  << std::boolalpha << std::accumulate(b.begin(), b.end(), true, forall) << endl;
    cout << "Exists acc: "  << std::boolalpha << std::accumulate(b.begin(), b.end(), false, exists) << endl;


}
