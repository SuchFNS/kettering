#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct table{
	string atomicSymbol;
	string name;
	int atomicNum;
	double mass;
};
//prototypes
void display(string, int);

int main(){
	string symbol;
	int atomic;
	//call for inputs
	display(symbol, atomic);
	
	cout << symbol;
}
void display(string &symbol, int &atomic){
	int decision;
	cout << "Will you input the Element Symbol (1) or the Atomic Number(2)?\n";
	cin >> decision;
	if (decision == 1){
		cout << "Input the Element Symbol now\n";
		cin >> symbol;
	}else{
		cout << "Input the Atomic Number now\n";
		cin >> atomic;
	}
	symbol[0] = toupper(symbol[0]);
}
