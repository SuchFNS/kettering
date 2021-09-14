/*
Colin Quinn and Elena Bucciarelli
Assignment 4

Create a best fit, worst fit, and first fit
memory allocation program.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

typedef struct memoryBlock {
    char* id;
    int startLocation;
    int endLocation;
    struct memoryBlock* next;
} memoryBlock;

struct memoryBlock* head;
int bufSize = 50;

//prototypes
void createHead(int startBlockSize);
void getUserInput();
char* convertToUpper(char* buf);

int main(int argc, char* argv[]) {
    //check parameters
    if (argc != 2) {
        printf("Please include a starting memory size.\nExiting...\n");
        return 1;
    }
    //get start size
    int startBlockSize = atoi(argv[1]);
    if (startBlockSize <= 0) {
        printf("Starting memory size must be larger at least 1.\nExiting...\n");
        return 1;
    }

    createHead(startBlockSize);

    getUserInput();

}
//covnert string to uppercase
char* convertToUpper(char* buf) {
    char* tmp;
    for (int i = 0; i < strlen(buf); i++) {
        tmp[i] = toupper(buf[i]);
    }
    return tmp;
}

void getUserInput() {
    int doneFlag = 0;
    char* buf[bufSize];

    while (!doneFlag) {
        if (readline("Allocator > ", buf, bufSize) > 0) {
            printf("Input was too long, maximum buffer size is: %dkb\n", bufSize);
            continue;
        }
        //convert buffer to uppercase
        char* convBuf = convertToUpper(buf);
        //case for requesting memory
        if (strncmp(convBuf, "RQ", 2) == 0) {
            
        }
    }
}

//create the head node of the linked list
void createHead(int startBlockSize) {
    head = (struct memoryBlock*) malloc(sizeof(memoryBlock));
    head->id = "Unused";
    head->startLocation = 0;
    head->endLocation = startBlockSize - 1;
    head->next = NULL;
}

