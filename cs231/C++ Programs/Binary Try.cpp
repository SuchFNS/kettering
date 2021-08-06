// Project Name: Lab for Sorting Arrays
//Programmer Name: Colin Quinn
//Date Written: October 26, 2017
/*Description: takes an array of lottery tickets, analyzes the input
	through binary search to check if the player's ticket is the 
	winning number. Also contain output of the number comparisons*/
	
#include <iostream>//IO
using namespace std;
//prototypes
int isWinner(int, int[]);

int main(){
	//variables and declarations
	int numbers[] = {13579, 26791, 26792, 33445, 55555,
				 	62483, 77777, 79422, 85647, 93121};
	int winner, runs;
	int hold, a, b;
	//input for the winning number
	cout << "Lab Part B: Binary Search\n";
	cout << "Input the winning numbers to check for matches\n";
	cin >> winner;


	//calls function to find if player wins with the
	//input numbers as the winners
	int wins = isWinner(winner, numbers);
	if (wins > 0){
		cout << "You are a Winner, your " << wins << "th number is your number!\n";
	}else cout << "You are a loser\n";
	
	//job termination
    cout << "Normal Job Termination\n";
    return 0;
}
//is called to run binary search to check if there is a matching number
int isWinner(int winner, int numbers[]){
	//variables
    int first = 0, last = 9, middle;                        
	//searches for a matching winning number
    while (first <= last){
        middle = (first + last) / 2; 
        if (numbers[middle] == winner){
            return middle;
        }else if (numbers[middle]> winner){
            last = middle - 1;
        }else {
            first = middle + 1;
        }
    }
    //returns -1 if you are a loser
    return -1; 
}
