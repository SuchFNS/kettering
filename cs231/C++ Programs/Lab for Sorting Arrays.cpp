// Project Name: Lab for Sorting Arrays
//Programmer Name: Colin Quinn
//Date Written: October 26, 2017
/*Description: uses bubble and selection sorting to sort two separate arrays
	in ascending order each using opposite sorting styles in different functions.*/
	
#include <iostream>//IO
using namespace std;
//prototypes 
int bubble(int[], int&);
int selection(int[], int&);
int main(){
	int runsBubble, runsSelection;
	
	int bubbleSort[] = {67, 90, 102, 4, 16, 32, 18, 23, 2, 112, 
						78, 43, 26, 13, 37, 22, 96, 82, 32, 54};
	int selectionSort[] = {67, 90, 102, 4, 16, 32, 18, 23, 2, 112, 
							78, 43, 26, 13, 37, 22, 96, 82, 32, 54};
	//calls bubble sort to sort the bubbleSort array				
	runsBubble = bubble(bubbleSort, runsBubble);
	
	//outputs the bubble sort method with amount of runs
	for (int i = 0; i < 20; i++){
		cout << bubbleSort[i] << " ";
	}
	cout << endl << runsBubble << " runs through a bubble sort\n\n";
	
	//calls selection to sort the selectionSort array
	runsSelection = selection(selectionSort, runsSelection);
	//outputs the sorted array from Selection sorting function
	for (int i = 0; i < 20; i++){
		cout << selectionSort[i] << " ";
	}
	cout << endl << runsSelection << " runs through a Selection Sort\n\n";
	//Says which is more efficient
	if (runsBubble > runsSelection){
		cout << "Selection Sorting is more efficient\n";
	}else cout << "Bubble Sorting is more efficient\n";
	
	//job termination
	cout << "Normal Job Termination\n";
	return 0;
}

//function to sort the array using bubble sort
int bubble(int bubbleSort[], int& runsBubble){
	
	bool swapped;
	for (int i = 0; i < 20-1; i++){
    	swapped = false;
    	for (int j = 0; j < 20-i-1; j++){
        if (bubbleSort[j] > bubbleSort[j+1]){
           swap(bubbleSort[j], bubbleSort[j+1]);
           swapped = true;
    	}
    }
     runsBubble++;
     // IF no two elements were swapped by inner loop, then break
     if (swapped == false)
        break;
	}
   return runsBubble;
}

//function to sort the array using selection sort
int selection(int selectionSort[], int& runsSelection){
	
	int i, j, min;
    // One by one move boundary of unsorted subarray
    for (i = 0; i < 19; i++){
        // Find the minimum element in unsorted array
        min = i;
        for (j = i+1; j < 20; j++)
          if (selectionSort[j] < selectionSort[min])
            min = j;
        // Swap the found minimum element with the first element
        swap(selectionSort[min], selectionSort[i]);
        //adds 1 each iteration
        runsSelection++;
    }
	return runsSelection;
	
}
