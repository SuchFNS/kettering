// Project Name: Assignment #2, Pizza Slices
// Programmer Name: Colin Quinn	
// Date Written: September 7, 2017
// Description: Calculates the amount of slices able to be made out of a pizza.

#include <iostream> //ALlows for input and output
#include <math.h> // allows for pow function
#include <iomanip>//allows to round to one decimal
 using namespace std;
 
 //main function
 int main ()
 {
 	//declaration of variables 
 	double diameter, slices, radius, area;
 	const double sliceSize = 14.125, pi = 3.14159;
 	
 		//Assignment clarification
	cout << "Assignment #2, Number of Pizza Slices. \n";
	cout << "Colin Quinn \n";
 	
 	//input output sequence to gain needed info.
 	cout << "What is the diameter of the pizza in inches? \n";
 	cin >> diameter;
 	
 	//math to achieve the needed result.
 	radius = diameter / 2;
 	area = pi * pow(radius, 2);
 	slices = area / sliceSize;
 	
 	//output statement
 	cout << setprecision(2);
 	cout << "You can have " << slices << " slices with a " << diameter << " diameter pizza.\n";
 	
 	//termination statement
 	cout << "Normal Termination. \n";
 	system("pause");
 	return 0;
 		
 }
