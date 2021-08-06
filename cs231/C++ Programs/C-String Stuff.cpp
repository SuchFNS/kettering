#include <iostream> //IO
using namespace std;
//prototypes
int length(char[]);
int main(){
	const int SIZE = 51;
	char sentence[SIZE];
	int count = 0;
	cout << "Input a sentence no longer than 50 characters\n";
	cin.getline(sentence, count);
	count = length(sentence);
	cout << count << " characters long\n";
}
//finds the length of the array
int length(char sentence[]){
	int i = 0;
	while (sentence[i] != '\0'){
		i++;
	}
	return i;
}
