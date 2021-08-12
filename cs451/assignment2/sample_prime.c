// MAKE SURE YOU USE LONG LONG INT AN ALSO PRINT USING %llu to print it Otherwise 
//negative numbers will appear. 
#include<stdio.h>
#include<stdlib.h>
long unsigned int calculatedPrime = 123400003;
void handler(int signum);
int checkPrimeAndPrint(unsigned long int toCheck);

int main(int argc, char** argv){
     

// Set up handlers here 
//
//
//     a
       int numPrinted = 0;
       long unsigned int numberToCheck = calculatedPrime +1; 
       while (numPrinted <10) {
           if (checkPrimeAndPrint(numberToCheck) ==1){ 
              printf("prime number is %lu \n", numberToCheck);
              numPrinted++;
           }
           numberToCheck++; 
         
       } 
        
}

        
void handler(int signum){
// Write handler code here. 


}

int checkPrimeAndPrint(unsigned long int toCheck){
      unsigned long int i = 2; 
      int prime = 1; 
      while (prime == 1&& i < toCheck/2){ 
              if (toCheck % i == 0) 
                prime = 0;
              i++;
      } 
      return (prime);
}
