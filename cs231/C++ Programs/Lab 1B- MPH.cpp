// Project Name: Assignment 1B- MPH
// Programmer Name: Colin Quinn	
// Date Written: August 31, 2017
// Description: Determines the average speed for a distance over time.

#include <iostream> // Header file to enable console I/O
using namespace std;

// Begin main Function Definition
int main( )
{
// Initialization
// Declare data objects:

double distance, time, speed; // Objects are data type double

// Display identification on screen:

cout << "Assignment 1B" << endl;
cout << "Colin Quinn" << endl << endl;

/* Input
Asks for the necessary information for the variables
*/

cout << "How far did you travel? (miles)" << endl;
cin >> distance;
cout << "How long did it take you? (hours)" << endl;
cin >> time;

// Processing
// Calculate area of rectangle and
// assign result to area data object:

speed = distance / time;

// Output
// Display results in a complete sentence:

cout << "Your average speed was " << speed << " miles per hour.";

// Termination
// Indicate normal EOJ:

cout << endl << "Normal job termination" << endl;
system("pause");
return 0;

}
// End of main function
