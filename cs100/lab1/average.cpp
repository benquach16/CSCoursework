//Written by
//Benjamin Quach and Ryota Saito

/* ex1
 * This program reads in a list of grades, calculates the average, and prints it to the terminal. 
 * Create your own inputs to test the program and make sure it runs correctly.
*/

#include <iostream>
#include <iomanip>
#include <fstream>

//added namespace
using namespace std;

int main()
{
   int grade;
   int numberOfGrades = 0;		//initialized to 0
   int totalGrades;
   float averageGrade;
   ifstream inputFile;

   const int SENTINEL = -999;

//  open the input file
   inputFile.open("gradesen.dat");

//  read in the grades, total them, and count how many grades there are
//  stop the loop when the sentinel is read
   inputFile >> grade;
   while (grade != SENTINEL)
   {
      cout << "Grade is:  " << grade << endl;
      totalGrades = totalGrades + grade;
      numberOfGrades = numberOfGrades + 1;
      inputFile >> grade;
   }

//  calculate and print the average
//cast to float!
   averageGrade = (float)(totalGrades) / numberOfGrades;
   cout << setiosflags(ios::fixed);
   cout << setiosflags(ios::showpoint);
   cout << setprecision(1);
   cout << "The average grade for the exam is :  " << averageGrade << endl;
}
