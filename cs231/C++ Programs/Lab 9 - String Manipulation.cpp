
#include <iostream>//IO
using namespace std;
//protoypes
int length(char[]);
int capitals(char[]);

int main(){
	//variables
	const int SIZE = 51;
	char sentence[SIZE];
	int ascii;
	//ask for input and store in a cstring
	cout << "Input a sentence with less than 50 characters.\n";
	cin.getline(sentence, SIZE);
	//call for the count function
	int count = length(sentence);
	cout << count << " characters entered\n";
	//calls for the capitals function
	capitals(sentence);
	//outputs the sentence
}
//finds amount of characters input in the sentence
int length(char sentence[]){
	int count = 0;
	//loop to count characters
	while (sentence[count] != '\0')
		count++;
	
	return count;
}
//capitalizes every letter
int capitals(char sentence[]){
	int i = 0;
	cout << "before loop\n";
	while (sentence[i] != '\0'){
		if (sentence[i] > 97 && sentence[i] < 122)
			sentence[i] -= 32;
		i++;	
	}
	cout << "after loop\n";
	return 0;
}
