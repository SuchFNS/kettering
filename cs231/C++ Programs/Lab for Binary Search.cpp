// Project Name: Lab for Sorting Arrays
//Programmer Name: Colin Quinn
//Date Written: October 26, 2017
/*Description: takes an array of lottery tickets, analyzes the input
	through binary search to check if the player's ticket is the 
	winning number. Also contain output of the number comparisons*/
	
#include <iostream>//IO
using namespace std;
//prototypes
bool isWinner(int[], int[]);

int main(){
	//variables and declarations
	int numbers[] = {13579, 26791, 26792, 33445, 55555,
				 	62483, 77777, 79422, 85647, 93121};
	int winner[5], runs;
	int hold, a, b;
	//input for the winning numbers
	cout << "Input the winning numbers to check for matches\n";
	for (int i = 0; i < 5; i++){
		cin >> winner[i];
	}
	//organization line
	cout << endl;
	//sorts the array from least to greatest
	for(a = 0; a < 4; a++){ 
		for(b = a+1; b < 5; b++){ 
    		if(winner[a] > winner[b]){ 
        		hold = winner[a]; 
        		winner[a] = winner[b]; 
        		winner[b] = hold; 
       		} 
    	} 
	}
	
	//calls function to find if player wins with the
	//input numbers as the winners
	bool wins = isWinner(winner, numbers);
	if (wins == 1){
		cout << "You are a Winner\n";
	}else cout << "You are a loser\n";
	
	//job termination
    cout << "Normal Job Termination\n";
}
bool isWinner(int winner[], int numbers[]){
	
	int low = 0, middle, high = 10;
	//binary search to find any matches
//this loop is not working properly, fix dat shit

	while(low <= high){
	    middle = (low + high) / 2;
		for (int i = 0; i < 10; i++){
		    if(numbers[middle] == winner[i]){
		        cout << winner[i] << " winning number\n";
		        cout << numbers[middle] << " is the middle number\n";
		        return 1;
		    }else if (numbers[middle] > winner[i]){
		        high = middle - 1;
		     	cout << "Incrementing High\n"; 
				cout << winner[i] << " is the winning number\n";
				cout << numbers[middle] << " is the middle number\n";  
		    }else{
		        low = middle + 1;
			}
		}
	}
	return 0;
}
