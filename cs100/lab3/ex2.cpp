#include <iostream>

using namespace std;


class Calculator
{
public:
  Calculator() : stack(new int[10]), size(0)
  {
  }
  ~Calculator()
  {
    delete [] stack;
  }
  void add(int num1, int num2)
  {
    push(num1);
    push(num2);
    cout << pop() + pop() << endl;
  }
  void sub(int num1, int num2)
  {
    push(num2); //backwards subtraction
    push(num1);
    cout << pop() - pop() << endl;
  }

  void mul(int num1, int num2)
  {
    push(num1);
    push(num2);
    cout << pop() * pop() << endl;
  }

  void push(int num)
  {
    stack[size] = num;
    size++; // size should increase after stack inc
  }

  int pop()
  {
    size--;
    return stack[size]; // double subtraction
  }
private:
  int *stack;
  int size; //changed from unsigned to signed 
};

int main()
{
  char input;
  bool quit = false;
  Calculator cal;

  while(!quit)
    {
      cin >> input;
      switch(input)
	{
	case 'a':
	  {
	    cout << "Adding numbers simulator, input yo numbers ";
	    int num1, num2;
	    cin >> num1;
	    cin >> num2;
	    cal.add(num1, num2);
	    quit = true;
            break; //forgot all break statements
	  }
	case 's':
	  {
	    cout << "Subtraction simulator, input yo numbers ";
	    int num1, num2;
	    cin >> num1;
	    cin >> num2;
	    
	    cal.sub(num1, num2);
	    quit = true;
            break; // no break
	  }
	case 'm':
	  {
	    cout << "Multiplication simulator, input yo numbers ";
	    int num1, num2;
	    cin >> num1;
	    cin >> num2;
	    cal.mul(num1, num2);
	    quit = true;
	    break;
	  }
	}
    }
  return 0;
}
