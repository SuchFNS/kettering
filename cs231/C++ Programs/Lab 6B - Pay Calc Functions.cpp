// Project Name: Lab 6B - Pay Calculation Functions
//Programmer Name: Colin Quinn
//Date Written: October 10, 2017
//Description: Calculate pay using separate functions 
	//use one to display, check for code validity, and calculate pay
	//I lost my Lab 5A due to flashdrive problems. Some minor things may be missing, I apologive for the inconvenience.

#include <iostream>//input output
#include <iomanip>//output manipulation
using namespace std;

//prototypes
void Display(void);
bool CodeNotValid(char);
double GetPay(char, double, double);

int main(){
	
	//variables
	int id;
	double income, hours;
	char code, repeat;
	//displays program clarification
	Display();
	//sets do while loop
	do {

		//input output to gain needed info
		cout << "Enter Employee Number\n";
		cin >> id;
		cout << "Enter Pay Code\n";
		cin >> code;
		
		//check if paycode is valid
		bool CodeNotValid(char code);
		//if paycode is valid, then it continues on
		if (CodeNotValid(code)){
			//asks hours worked
			cout << "Enter hours worked\n";
			cin >> hours;
		}else cout << "Invalid Pay Code\n";
		
		//calls getPay function
		GetPay(code, hours, income);
		//asks for new inputs for new employees
		cout << "Would you like to enter another employee? (Y/N)\n";
		cin >> repeat;
	//checks for an ending in the loop
	}while(repeat == 'Y' || repeat == 'y');
	
	//job termination
	cout << "Have a good day!\n";
	return 0;
}

//display assignment clarification
void Display(void){
	//Assignment clarification
	cout << "Lab 6B - Pay Calculation Functions\n";
	cout << "Colin Quinn\n";
}
//function to check if a valid paycode is entered
bool CodeNotValid(char code){
 
	//checks proper paycodes
		if (code == 'M' || code == 'm'){
		//checks if M is entered
			return 1;
		//checks if 'O' is entered
		} else if (code == 'O' || code == 'o'){
			return 1;
		//checks if 'T' is entered
		}else if (code == 'T' || code == 't'){
			return 1;
		//trailing else to show who has an improper paycode
		} else return 0;
	
}
//calculate their pay based on amount of hours worked and paycode
double GetPay(char code, double hours, double income){

	//sets minimum wage
	const double MIN_WAGE = 8.90;
	//variables for the math
	double payrate, ot, money;
	
	//adjusts for overtime hours.
	ot = (hours > 40) ? hours - 40 : 0;
	hours = (hours > 40) ? 40 : hours;
		
	//checks proper paycodes
	if (code == 'M' || code == 'm'){
		//calculates if 'm' is the paycode entered
		payrate = hours * MIN_WAGE;
		money = ot * (MIN_WAGE * 1.50);
		income = payrate + money;
	//calculates for 'O' employees
	} else if (code == 'O' || code == 'o'){
		payrate = hours * (MIN_WAGE + 1.00);
		money = ot * ((MIN_WAGE + 1) * 1.5);
		income = payrate + money;
	//calculates for 'T' employees
	}else if (code == 'T' || code == 't'){
		payrate = hours * (MIN_WAGE + 2.00);
		money = ot * ((MIN_WAGE + 2.00) * 1.5);
		income = payrate + money;
	}
	//resets hours 
	hours = hours + ot;
	//outputs hours payrate and income
	cout << "At a rate of " << payrate / hours << ", you earned $" << income << endl;
	
	//returns income
	return income;
}
