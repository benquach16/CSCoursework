//Written by
//Benjamin Quach and Ryota Saito

//ex4

#include <iostream>
using namespace std;

class CSquare
{
public:
    double Side;

    CSquare() : Side(0.00) {}
    CSquare(double side) : Side(side) { }
    ~CSquare() { }

    double getSide() const { return Side; }
    void setSide(const double s)
    {
	if( s <= 0 )
		Side = 0.00;
	else
		Side = s;		//dont cast to int
	}

    double Perimeter() { return Side * 4; }
    double Area() { return Side * Side; }
};

int main()
{
    CSquare *sqr[4];

    sqr[0] = new CSquare;
    sqr[0]->setSide(24.55);		//Is a pointer
    sqr[1] = new CSquare;
    sqr[1]->setSide(15.08);		//Is a Pointer
    //initialize index 2
    sqr[2] = new CSquare;
    sqr[2]->setSide(10);
    sqr[3] = new CSquare;
    sqr[3]->setSide(202.24);		//is a pointer


	//CHANGED THE INDICES BECAUSE THEY STARTED AT 0
    cout << "Squares Characteristics" << endl;
    cout << "Square 1" << endl;
    cout << "Side:      " << sqr[0]->getSide() << endl;		//-> pointer type
    cout << "Perimeter: " << sqr[0]->Perimeter() << endl; 	//-> pointer type
    cout << "Area:      " << sqr[0]->Area() << endl;		//-> pointer type

    cout << "Square 2" << endl;
    cout << "Side:      " << sqr[1]->getSide() << endl;		//-> pointer type
    cout << "Perimeter: " << sqr[1]->Perimeter() << endl;//-> pointer type
    cout << "Area:      " << sqr[1]->Area() << endl;//-> pointer type

    cout << "Square 3" << endl;
    cout << "Side:      " << sqr[2]->getSide() << endl;//-> pointer type
    cout << "Perimeter: " << sqr[2]->Perimeter() << endl;//-> pointer type
    cout << "Area:      " << sqr[2]->Area() << endl;//-> pointer type
	
    cout << "Square 4" << endl;
    cout << "Side:      " << sqr[3]->getSide() << endl;//-> pointer type
    cout << "Perimeter: " << sqr[3]->Perimeter() << endl;//-> pointer type
    cout << "Area:      " << sqr[3]->Area() << endl;//-> pointer type

    return 0;
}
