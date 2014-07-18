//Written by
//Benjamin Quach and Ryota Saito

//ex2: Program takes up to MAXSIZE number of integers and outputs their sum

#include <iostream>

using namespace std;

//BEN: Added function prototypes
int arraysum(const int n, const int a[]);

int main()
{
	const int MAXSIZE = 50;
	int a[MAXSIZE];
	int n;
	cout << "Enter up to " << MAXSIZE << 
		" integers, ctrl-D to end:\n";
	n = 0;
	while ((n < MAXSIZE) && (cin >> a[n])) 
		n++;		//syntax error
	if (n == 0)
		cout << "nothing entered!\n";
	else
		cout << "sum of input integers = " << 
			arraysum(n, a) << endl;
	return 0 ;
}

// ---- function definition ----

int arraysum(const int n, const int a[])
{
	if (n == 0)
		return 0;			//Changed it to 0 to prevent an accidential addition
	else
		return a[n-1] + arraysum(n-1, a);
}
