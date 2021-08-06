// Project Name: Assignment #5: Student Grade Calculator
//Programmer Name: Colin Quinn
//Date Written: October 15, 2017
/*Description: Will open file, read the Name and grades, then using functions
	will output the student name, calculate their final grade using the teacher's 
	grading scale, assign a letter grade to each percentile, and display whether
	the student has passed or failed based on grade and attendance. */

#include <iostream>//includes io
#include <fstream>//includes file usage
#include <string>//includes strings
#include <iomanip>//io manipulation
using namespace std;

//prototypes
void reportHeader(string&, string&);
double average(int, int, int, int, int, int);
bool PassFail(int, double);

int main(){
	
	//variables
	ifstream infile;
	string first, last, grade;
	double avg;
	int test1, test2, as1, as2, as3, as4, attendance;
	bool pass;
			
	//open input file
	infile.open("studentlist.txt");
	if (!infile){
		cout << "In file open failure";
	}
	
	//do while loop to repeat the process as needed
	do {

		//gains student's name
		infile >> first;
		infile >> last;
		//calls function to display the student name
		reportHeader(first, last);
		//calls function to read the student's grades
			//and then calculates the average grade
		infile >> test1;
		infile >> test2;
		infile >> as1;
		infile >> as2;
		infile >> as3;
		infile >> as4;
		avg = average(test1, test2, as1, as2, as3, as4);
		
		//checks how many classes have been attended
		infile >> attendance;
		pass = PassFail(attendance, avg);
		// outputs in a formatted way with manipulated IO
		cout << test1 << " " << test2 << " " << as1 << " " << as2 << " " << as3 << " " << as4 << endl;
		//fixes percentage to 2 decimal places
		cout << fixed << setprecision(2); 
		cout << avg << "%  ";
		//if statement to find letter grade
		if (100 >= avg && avg >= 90){
			grade = 'A';
		}else if (89 >= avg && avg >= 80){
			grade = 'B';
		}else if (79 >= avg && avg >= 70){
			grade = 'C';
		}else if (69 >= avg && avg >= 60){
			grade = 'D';
		}else grade = 'F';
		//back to output sequence
		cout << grade << endl;
		cout << attendance << " classes attended\n";
		//if statement to check if they pass or fail
		if (pass == 1 ){
			cout << "You Passed the Class!\n"  << endl;
		}else cout << "You Failed the Class\n" << endl;
		
		
		
	//ends the do while loop when the file is done	
	}while (!infile.eof());
	//closes the input file when done
	infile.close();
}
//displays the student's name for the user
void reportHeader(string &first, string &last){
	cout << first << " " << last << "	";
		
}
//will calculate the average grade for the student
double average(int test1, int test2, int as1, int as2, int as3, int as4){
	
	double assignmentAvg, avg;
	//averages the assignment grades
	assignmentAvg = (as1 + as2 + as3 + as4) / 4;
	//averages the tests and the assignments to get end grade
	avg = (test1 + test2 + assignmentAvg) / 3;
	return avg;
}

//will determine if the student passes or fails the class when called
bool PassFail(int attendance, double avg){

	//if statement to meet the proper passing requirements
	if (attendance >= 20 && avg >=60){
		return 1;
	}else return 0;
}



