//ben quach and rachel law
#include <iostream>
#include <queue>
#include <functional>
using namespace std;

int main()
{
  priority_queue<pair<int, int>, deque<pair<int, int> >, greater<pair<int,int> > > pq;
  //priority_queue<int> mypq;
  pq.push(pair<int, int>(5,35));
  pq.push(pair<int, int>(124,89));
  pq.push(pair<int, int>(1,125));
  pq.push(pair<int, int>(24,55));
  while(!pq.empty())
    {
      cout << pq.top().first << "jobid: " << pq.top().second << endl;
      pq.pop();
    }


  
}
