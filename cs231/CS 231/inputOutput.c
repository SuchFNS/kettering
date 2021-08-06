// Colin Quinn
// CS 231-03L
// Get input from console and add two integers, output sum


#include <stdio.h>
int main(){

	int num1, num2, sum;
	
	//ask for first number
	printf("Enter an integer: ");
	scanf("%d", &num1);

	printf("Enter another integer: ");
	scanf("%d", &num2);

	//add the two numbers
	sum = num1 + num2;

	//output the sum
	printf("The sum of %d + %d = %d", num1, num2, sum);

	return 0;
}
