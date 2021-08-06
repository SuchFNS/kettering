// Project Name: Lab #6A - MPH Functions
//Programmer Name: Colin Quinn
//Date Written: October 8, 2017
//Description: Use a separate function to calculate miles per hour

#include <iostream>//io
using namespace std;

//prototypes
double mph(double, double);

int main(){
	//variables
	double distance, time, speed;
	
	//clarification
	cout << "Lab 6A: Miles Per Hour with Functions\n";
	cout << "Colin Quinn\n";
	
	//input output for speeds needed
	cout << "Enter your distance travelled (miles)\n";
	cin >> distance;
	cout << "Enter how long it took you (hours)\n";
	cin >> time;
	
	//call the mph function
	speed = mph(distance, time);

	//outputs miles per hour
	cout << speed << " miles per hour\n";
	
	//job termination
	cout << "Normal Job Termination\n";
	return 0;
	system("pause");
	
}
//function to calculate miles per hour
 double mph(double distance, double time){
 	//calculates the speed and returns to main
	double speed;
	speed = distance / time;
	return speed;
}
