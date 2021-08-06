#include <iostream>
using namespace std;

struct Student{
	string name;
	int idNum;
	int scores[];
	double average;
	char grade;
};
//prototypes 
void calcAverage(Student[], int, int);
int main(){
	//variables
	int numstudents = 0;
	int tests = 0;
	//input output for basic info
	cout << "How many students are there?\n";
	cin >> numstudents;
	cout << "How many tests were there?\n";
	cin >> tests;
	//creates the student list array
	Student list[numstudents];
	//loop input output to gain the student information
	for (int i = 0; i < numstudents; i++){
		cout << "Enter Name\n";
		cin.ignore();
		getline(cin, list[i].name);
		cout << "Enter Student ID\n";
		cin >> list[i].idNum;
		cout << "Enter Test Scores.\n";
		int j = 0;
		while (j < tests){
			cin >> list[i].scores[j];
			j++;
		}
	}
	//call to calculate the average and assign grade
	calcAverage(list, tests, numstudents);
	
	//loop to output all of the information for the students
	for (int i = 0; i < numstudents; i++){
		cout << "Name:\t" << list[i].name << endl; 
		cout << "Student ID:\t" << list[i].idNum << endl;
		cout << "End Grade:\t" << list[i].average << endl;
		cout << "Letter Grade:\t" << list[i].grade << endl;
		cout << endl;
	}
		
}

//calculates the average score and assigns the grade earned.
void calcAverage(Student list[], int tests, int numstudents){
	int total;
	//finds total test scores out of all of them
	for (int i = 0; i < numstudents; i++){
		for (int j = 0; j < tests; j++){
			total += list[i].scores[j];
		}
		//averages the scores and resets total
		list[i].average = total / tests;
		total = 0;
	}
	//assigns letter grades for each student
	for (int i = 0; i < numstudents; i++){
		if (list[i].average <= 100 && list[i].average >= 91){
			list[i].grade = 'A';
		}else if (list[i].average <= 90 && list[i].average >= 81){
			list[i].grade = 'B';
		}else if (list[i].average <= 80 && list[i].average >= 71){
			list[i].grade = 'C';
		}else if (list[i].average <= 70 && list[i].average >= 61){
			list[i].grade = 'D';
		}else list[i].grade = 'F';
	}

}
