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
	int winner[5], runs;
	bool money;
	
	


	//uses binary search to find a matching number
	while(low<=high)
    {
    	int middle = (low+high)/2;
        if(arr[middle] == searchValue)
            return true;
        else if (arr[middle] > searchValue)
            high = middle - 1;
        else
            low = middle + 1;
    }
    return false;

	
}
