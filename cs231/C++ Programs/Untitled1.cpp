#include <iostream>//IO
using namespace std;
//protoypes
int length(char[]);
void capitalized(char[]);
void findVowel(char[], int&, int&, int&, int&, int&);

int main(){
	//variables
	int a, e, i, o, u;
	const int SIZE = 51;
	char sentence[SIZE];
	//ask for input and store in a cstring
	cout << "Input a sentence with less than 50 characters.\n";
	cin.getline(sentence, SIZE);
	//call for the count function
	int count = length(sentence);
	cout << count << " characters entered\n";
	//calls for the capitals function
	
	//calls to count each vowel
	findVowel(sentence, a, e, i, o, u);
	
}
//finds amount of characters input inthe sentence
int length(char sentence[]){
	int count = 0;
	//loop to count characters
	while (sentence[count] != '\0')
		count++;
	
	return count;
}
//capitalizes every letter in the cstring
void capitalized(char sentence[]){
	int i = 0;
	while (sentence[i] != '\0'){
		if (sentence[i] < 122 && sentence[i] > 122)
			sentence[i] -= 32;
	}
}
//finds the amount of each vowel in the string entered
void findVowel(char sentence[], int& a, int& e, int& i, int& o, int& u){
	int c = 0;
	while (sentence[c] != '\0'){
		if (sentence[c] == 'a'){
			a++;
		}else if (sentence[c] == 'e'){
			e++;
		}else if (sentence[c] == 'i'){
			i++;
		}else if (sentence[c] == 'o'){
			o++;
		}else if (sentence[c] == 'u'){
			u++;
		}
	}
}

