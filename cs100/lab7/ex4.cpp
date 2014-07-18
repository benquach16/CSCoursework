//ben quach and rachel law

#include <iostream>
#include <vector>

using namespace std;

class my_set
{
public:
  vector<int> v;
  vector<int> dunion(my_set v2)
  {
    vector<int> ret;
    
    set_union(v.begin(), v.end(), v2.v.begin(), v2.v.end(), inserter(ret, ret.end()));
    return ret;
    
  }
  vector<int> dintersection (my_set v2)
  {
    vector<int> ret;

    set_intersection(v.begin(), v.end(), v2.v.begin(), v2.v.end(), inserter(ret, ret.end()));
    return ret;
  }
  bool dinclusion(my_set v2)
  {
    if (v.size()==0) return true;
    //we check if everything in v2 is in v
    for(unsigned i = 0 ; i < v2.v.size(); i++)
      {
	bool found = false;
	for(unsigned n = 0; n < v.size(); n++)
	  {
	    if(v2.v[i] == v[n])
	      {
		//found it
		found = true;
	      }
	  }
	if(!found)
	  return false;
      }
    return true;
  }

  vector<int> ddifference(my_set v2)
  {
    vector<int> ret(1);
    set_difference(v.begin(), v.end(), v2.v.begin(), v2.v.end(), ret.begin());

    return ret;
  }
  void print(string msg)
  {
    cout << msg << endl;
    for(vector<int>::iterator i = v.begin(); i!= v.end(); i++)
      cout << (*i) << " ";
    cout << endl;

  }
};

 

int main()
{
  my_set uni1;
  uni1.v.push_back(1);
  uni1.v.push_back(3);
  uni1.v.push_back(4);
  my_set uni2;
  uni2.v.push_back(2);
  my_set uni3;
  uni3.v = uni1.dunion(uni2);
  uni3.print("UNION");

  my_set int1;
  int1.v.push_back(1);
  int1.v.push_back(2);
  int1.v.push_back(3);
  my_set int2;
  int2.v.push_back(1);
  int2.v.push_back(2);
  my_set int3;
  int3.v = int1.dintersection(int2);
  int3.print("INTERSECTION");

  my_set inc1;
  inc1.v.push_back(1);
  my_set inc2;
  inc2.v.push_back(2);
  inc2.v.push_back(1);
  cout << "INCLUSION (bool value)" << endl;
  cout << inc2.dinclusion(inc1) << endl;
  cout << inc1.dinclusion(inc2) << endl;  

  my_set dif1;
  dif1.v.push_back(1);
  dif1.v.push_back(4);
  my_set dif2;
  dif2.v.push_back(1);
  my_set dif3;
  dif3.v = dif1.ddifference(dif2);
  dif3.print("DIFFERENCE");

}
