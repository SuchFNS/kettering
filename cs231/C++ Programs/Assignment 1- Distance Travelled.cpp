// Project Name: Assignment #1, Distance Travelled
// Programmer Name: Colin Quinn	
// Date Written: September 3, 2017
// Description: Calculates the maximum distance a car can travel on one tank of gas.

#include <iostream> //Allows for input and output
using namespace std;

//main function
int main(){
	//declaration of variables and constants, using doubles
	double distanceHighway, highwayInput, distanceCity, cityInput, overallDistance, gasUsed;
	const double highway = 20.4;
	const double city = 16.2;
	
	//Assignment clarification
	cout << "Assignment #1, Distance Travelled" << endl;
	cout << "Colin Quinn" << endl;
	
	//input output sequence to receive information required to calculate
	cout << "How much gas used on the highway?" << endl;
	cin >> highwayInput;
	cout << "How much gas used in the city?" << endl;
	cin >> cityInput;
	
	//calculations for the total distance travelled
	distanceHighway = highwayInput * highway;
	distanceCity = cityInput * city;
	overallDistance = distanceCity + distanceHighway;
	gasUsed = cityInput + highwayInput;
	
	//outputs the answer in a full sentence
	cout << "The car travelled " << overallDistance << " miles on " << gasUsed << " gallons of gas.";
	
	//Terminates the command console
	cout << endl << "Normal Termination." << endl;
	system("pause");
	return 0;
		
}
//end of main function
