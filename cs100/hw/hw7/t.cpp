#include <deque>
#include <iostream>
using namespace std;

int main()
{
    deque<int> d;
    d.push_back(6);
    d.push_front(3);
    d.push_back(9);
    d.push_front(1);

    for(int i = 0; i < d.size(); i++)
	cout << d[i] << endl;
    d.pop_front();
    cout << d[0];
    return 0;
}
