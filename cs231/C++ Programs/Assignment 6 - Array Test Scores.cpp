// Project Name: Assignment 6 - Array Test SCores
//Programmer Name: Colin Quinn
//Date Written: October 25, 2017
/*Description: Uses an array to store test scores from a file, then using 
	functions, calculate average, Min/Max, standard deviation, and then 
	determine the quartile summary.*/

#include <iostream>//IO
#include <iomanip>//IO manipulation
#include <fstream>//enables file reading/writing
#include <math.h>
using namespace std;
//prototypes
double average(int[], int);
void MinMax(int[], int, int&, int&);
float deviation(int[], int, int);
void quartiles(int[], int);

int main(){
	//variables
	fstream infile;
	int scores[500];
	int count = 0, input;
	int min, max;
	
	//open and read the file, inputting the info to an array
	infile.open("TestScores.txt");
	//inputs information from txt file to the array
	if (infile.is_open()){
		int scores[500];
		while (!infile.eof() && count < 500){
			infile >> scores[count];
			count++;
		}
	}

	//outputs for organization and confirmation
	cout << count << " total entries from file\n";
	//call for the average of all entries and outputs it
	double averages = average(scores, count);
	cout << averages << " is the average\n";
	//calls function to find a min and max
	MinMax(scores, count, min, max);
	//outputs for the minimum and maximum
	cout << min << " is the smallest in the array\n";
	cout << max << " is the largest in the array\n";
	
	//calls function to find the standard deviation
	float sd = deviation(scores, count, averages);
	cout << sd << " is the standard deviation from the average\n";
	
	//call for finding the quartile scores
	quartiles(scores, count);	
	
}
//finds the average
double average(int scores[], int count){
	int total;
	for (int i = 0; i < count; i++){
		total += scores[i];
	}
	cout << total << " is the sum of the entries\n";
	double averages = total / count;
	return averages;
}
//finds the maximum and minimum values
void MinMax(int scores[], int count, int& min, int& max){
	//find the minimum value
	min = scores[0];
	for (int i = 1; i < count; i++){
		if (scores[i] < min)
			min = scores[i];
	}
	//finds the maximum value
	max = scores[0];
	for (int i = 1; i < count; i++){
		if (scores[i] > max)
			max = scores[i];
	}	
}
//finds the deviation of the array from its average
float deviation(int scores[], int count, int averages){
	//variable
	float sd, sum, mean;
	int i;
	//loops to add then find the average
	for (i = 0; i < count; i++){
		sum += scores[i];
	}
	mean = sum / count;
	//loop to find the standard deviation
	for (i = 0; i < count; i++){
		sd += pow(scores[i] - mean, 2);
	}
	return sqrt(sd / count);
		
}
//finds the amount of entries within each quartile and outputs it
void quartiles(int scores[], int count){
	int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
	//loop to check each number in the array
	for (int i = 0; i < count; i++){
		//determines which quartile the number belongs in
		if (scores[i] <= 100 && scores[i] >= 75){
			q1++;
		}else if (scores[i] < 75 && scores[i] >= 50){
			q2++;
		}else if (scores[i] < 50 && scores[i] >= 25){
			q3++;
		}else if (scores[i] < 25 && scores[i] >= 0){
			q4++;
		}
	}
	//outputs quartiles
	cout << q1 << " Scores in Quartile 1\n";
	cout << q2 << " Scores in Quartile 2\n";
	cout << q3 << " Scores in Quartile 3\n";
	cout << q4 << " Scores in Quartile 4\n";
}

