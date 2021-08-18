/* 
*   By: Colin Quinn and Elena Bucciarelli
*   Assignment 2 prime.c
*   
*   This program acts as a child process to be spawned by srtfScheduler.c.
*   Calculate a prime number with 10 digits to take up time and use 
*   signal handlers to send status information back to the parent process.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>

char* id;
char* pid;
unsigned long int primeFound = 0;

void handler(int signalSource) {
    //check what type of signal to handle
    if (signalSource == SIGSTOP) {
        printf("\nChild: Process %s: PID: %s: I am getting suspended.\n", id, pid);
    }else if (signalSource == SIGTERM) {
        printf("\nChild: Process %s: PID: %s: I am getting terminated.\n", id, pid);
    }else if (signalSource == SIGCONT) {
        printf("\nChild: Process %s: PID: %s: I am continuing execution.\n", id, pid);
    }
    //print the highest prime found
    if (primeFound == 0) {
        printf("\tChild: There have been no primes found yet\n");
    }else printf("\tChild: The highest prime I have found is: %lu\n", primeFound);
}

//find prime numbers with infinite loop to keep process going until sigterm is given
void findPrimes(unsigned long int num) {
    unsigned long int i = 3;
    unsigned long int midpoint = num / 2;
    while (1) {
        while (i < midpoint) {
            if (num % i == 0) {
                primeFound = num;
                break;
            }
            i++;
        }
        num++;
    }
}

int main (int argc, char* argv[]) {
    //initialize the id's needed from fork call
    id = argv[1];
    pid = argv[2];

    //handlers
    signal(SIGSTOP, handler);
    signal(SIGCONT, handler);
    signal(SIGTERM, handler);

    //get random number in range: number = (rand() % (upper - lower + 1)) + lower
    //formula found here: https://www.includehelp.com/c-programs/generate-random-numbers-within-a-range.aspx
    srand(time(NULL));  //srand gives a new rand() generated number, other it does not generate a new number.
    unsigned long int num = (rand() % (9999999999 - 1000000000 + 1)) + 1000000000;

    printf("Child: New process: %s. Beginning prime search at: %lu\n", id, num);

    findPrimes(num);
}