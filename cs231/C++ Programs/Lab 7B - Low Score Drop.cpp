// Project Name: Lab 7B - Lowest Score Drop
//Programmer Name: Colin Quinn
//Date Written: October 17, 2017
//Description: Take the test scores and use functions to find the lowest 
	//score and drop that, then take the average of the other 4 tests.

#include <iostream>//IO
#include <iomanip>//IO manipulation
using namespace std;
//prototypes
void getScore(int&, int&, int&, int&, int&);
double calcAverage(int, int, int, int, int);
int findLowest(int, int, int, int, int);

int main(){
	//variables
	int test1, test2, test3, test4, test5;
	//runs getScore() to ask for the user's test scores
	getScore(test1, test2, test3, test4, test5);
	//calls calcAverage() to get the average score with the curve
	double average = calcAverage(test1, test2, test3, test4, test5);
	
	//outputs your average score from calcAverage() with the lowest 
		//from getLowest() dropped.
	cout << average << " is your average score with the lowest dropped\n";
	
}

void getScore(int &test1, int &test2, int &test3, int &test4, int &test5){
	/*checks to see if input is between 100 and 0 for each test
		and forces a restart of the entering process*/
	cout << "Please input your first test score\n";
	cin >> test1;
	if (100>= test1 && test1 >= 0){
		cout << "Please input your second test score\n";
		cin >> test2;
		if (100 >= test2 && test2 >= 0){
			cout << "Please input your third test score\n";
			cin >> test3;	
			if (100 >= test3 && test3 >= 0){
				cout << "Please input your fourth test score\n";
				cin >> test4;	
				if (100 >= test4 && test4 >= 0){
					cout << "Please input your fifth test score\n";
					cin >> test5;
	//else statements to display where the user entered a wrong grade
	//and reruns this function until proper grades are input
				}else {
					(cout << "Your score is not within the grading scale\n");
					getScore(test1, test2, test3, test4, test5);
				}
			}else{
				(cout << "Your score is not within the grading scale\n");
				getScore(test1, test2, test3, test4, test5);
			}
		}else{
			(cout << "Your score is not within the grading scale\n");
			getScore(test1, test2, test3, test4, test5);
		}
	}else{
		(cout << "Your score is not within the grading scale\n");
		getScore(test1, test2, test3, test4, test5);
	}
}
//will calculate the average grade with the lowest score dropped
double calcAverage(int test1, int test2, int test3, int test4, int test5){
	//calls findLowest() to see which score to drop
	int lowest = findLowest(test1, test2, test3, test4, test5);
	//math to find the average score with the curve
	int average = ((test1 + test2 + test3 + test4 + test5) - lowest) / 4;
	//returns the average score to main()
	return average;
}

//find the lowest score input
int findLowest(int test1, int test2, int test3, int test4, int test5){
	//variable for the lowest score
	int lowest;
	//if statement to find the lowest score
	if (test2 < test1){
		lowest = test2;
	}else if (test3 < test2){
		lowest = test3;
	}else if (test4 < test3){
		lowest = test4;
	}else if (test5 < test4){
		lowest = test5;
	}else lowest = test1;
	//returns lowest score to calcAverage()
	return lowest;
}
