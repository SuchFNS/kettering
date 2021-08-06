// Project Name: Lab for Sorting Arrays
//Programmer Name: Colin Quinn
//Date Written: October 26, 2017
/*Description: takes an array of lottery tickets, analyzes the input
	through linear search to check if the player's ticket is the 
	winning number. Also contain output of the number comparisons*/
	
#include <iostream>//IO
using namespace std;

int main(){
	//variables and declarations
	int numbers[] = {13579, 26791, 26792, 33445, 55555,
					 62483, 77777, 79422, 85647, 93121};
	int winner, runs;
	bool wins = false;	 
	cout << "Enter the day's winning number\n";
	cin >> winner;
	//Linear search

		for(int i = 0; i < 10; ++i){
			//keeps track of how many runs the program does	
			runs++;
			//checks to see which number is a winner
			if(winner == numbers[i]){
		       	wins = true;
		       	break;
			}
		}
	if (wins == true){
		cout << "You are a winner!\n";
	}else cout << "You loser!\n";
	
	//output the number of runs
	cout << runs << " runs\n";
	//job termination
	cout << "Normal Termination";
	return 0;
}
