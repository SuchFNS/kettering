#include <iostream>

using namespace std;
//prototypes
int length(char[]);
void capitals(char[]);
void findVowels(char[], int, int&, int&, int&, int&, int&);

int main(){
	int a, e, i, o, u;
	const int SIZE = 51;
	char sentence[SIZE];
	//ask for input
	cout << "Please input a sentence no longer than 50 characters.\n";
	cin.getline(sentence, SIZE);
	//call for sentence character length
	int count = length(sentence);
	cout << count << " characters long\n";
	//call for capitalizing each letter
	
	
	//calls to find the vowels
	findVowels(sentence, count, a, e, i, o, u);
	cout << a << " times entered 'A\n";
	cout << e << " times entered 'E'\n";
	cout << i << " times entered 'I'\n";
	cout << o << " times entered 'O'\n";
	cout << u << " times entered 'U'\n";
	
	return 0;
}
//finds the length of the array
int length(char sentence[]){
	int i = 0;
	while (sentence[i] != '\0'){
		i++;
	}
	return i;
}
//capitalizes every letter
void capitals(char sentence[]){
	int i = 0;
	while (sentence != '\0'){
		if (sentence[i] >= 97 && sentence[i] <= 122)
			
		i++;
	}
}
//Finds the vowels
void findVowels(char sentence[], int count, int& a, int& e, int& i, int& o, int& u){
	int c = 0;
	while (sentence != '\0'){
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
