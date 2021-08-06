// Project Name: Assignment #4: Delta Wage Calculator
//Programmer Name: Colin Quinn
//Date Written: October 1, 2017
//Description: Read input from a file, calculate proper information, and output to a new file.

#include <iostream>//includes input output
#include <iomanip>//io manipulation
#include <string>// includes strings
#include <fstream>//file reading/writing
using namespace std;

int main(){
	//variables
	const double MIN_WAGE = 8.9, FED = 0.15, STATE = .05, SS = .075, MEDICARE = .015;
	int id = 0;
	double income, hours, payrate, ot, money, fed, state, ss, medicare;
	char code;
	ifstream infile;
	ofstream outfile;
	string first, last;
	
	//assignment clarification
	cout << "Assignment #4: Delta Wage Calculator\n";
	cout << "Colin Quinn\n";
	
	//gains inputs from file
	infile.open("payrolldata.txt.txt");
	outfile.open("payroll_report.txt");
	
	//check to see if files opened
	if (!infile){
		cout << "File Open Failure\n";
	}
	if (!outfile){
		cout << "Out File Open Failure\n";
	}
	
	//sets loop
	do {
		
		infile >> first;
		infile >> last; 
		infile >> id;
		infile >> code;
		infile >> hours;
		
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
			payrate = hours * (MIN_WAGE + 3.00);
			money = ot * ((MIN_WAGE + 3) * 1.5);
			income = payrate * money;
		//calculates for 'T' employees
		}else if (code == 'T' || code == 't'){
			payrate = hours * (MIN_WAGE + 6.00);
			money = ot * ((MIN_WAGE + 6.00) * 1.5);
			income = payrate + money;
		//trailing else to show who has an improper paycode
		} else outfile << "Invalid Paycode for " << first << " " << last << endl;
		
		//resets employee's hours and payrate
		payrate /= hours;
		hours += ot;
		
		//calculates how much is owed in taxes
		fed = income * FED;
		state = income * STATE;
		ss = income * SS;
		medicare = income * MEDICARE;
		
		//outputs paycheck information prior to taxes	
		outfile << setprecision(2) << fixed;
		outfile << "Employee Name: 		"
			<< first << " "
			<< last << endl;
		outfile << "Employee Code: 		"
			<< id << endl;
		outfile << "Payrate: 		" << payrate << endl;
		outfile << "Hours Worked: 		" << hours << endl;
		outfile << "Income before Taxes:	" << income << endl;
		
		//output for taxes owed
		outfile << "   Federal Income Tax 		" << fed << endl;
		outfile << "   State Income Tax 		" << state << endl;
		outfile << "   Social Security Tax 		" << ss << endl;
		outfile << "   Medicare Tax 		" << medicare << endl;
		
		//calculates income after taxes
		income -= fed;
		income -= state;
		income -= ss;
		income -= medicare;
		
		//outputs after tax income
		outfile << "Icome After Tax 	" << income << endl << endl;
		
		//resets all variables
		payrate = 0;
		hours = 0;
		income = 0;
		ot = 0;
		fed = 0;
		state = 0;
		ss = 0;
		medicare = 0;
		
	}while (!infile.eof());
	
	infile.close("payrolldata.txt.txt");
	outfile.close("payroll_report.txt");
	
}
