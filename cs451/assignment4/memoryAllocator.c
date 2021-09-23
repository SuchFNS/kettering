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
    char *id;
    int startLocation;
    int endLocation;
    struct memoryBlock* next;
} memoryBlock;

struct memoryBlock* head;
int bufSize = 50;
#define gapName "unused"

//prototypes
void createHead(int startBlockSize);
void getUserInput();
void getStatus();
int compact();
struct memoryBlock* swap(struct memoryBlock* firstNode, struct memoryBlock* nextNode, struct memoryBlock* prevNode);
int releaseProcess(char *id);
struct memoryBlock* mergeGapNodes(struct memoryBlock* currNode, struct memoryBlock* prevNode);
struct memoryBlock* firstFit(char *id, int size);
struct memoryBlock* bestFit(char* id, int size);
struct memoryBlock* worstFit(char* id, int size);
struct memoryBlock* insertNode(struct memoryBlock* node, char* id, int size);
void printBlockInfo(struct memoryBlock* node);
int getSize(struct memoryBlock* nodeInput);

int main(int argc, char* argv[]) {
    //check parameters
    if (argc != 2) {
        printf("Please include a starting memory size. Exiting...\n");
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

//the main loop of the program, handles UI and calls needed functions
void getUserInput() {
    int doneFlag = 0;
    char *buf;
    size_t len = 0;
    size_t chars;

    //create string to store input
    buf = (char*)malloc(bufSize * sizeof(char));
    if (buf == NULL) {
        printf("ERROR: unable to allocate buffer.");
        exit(1);
    }

    //main loop of program
    while (!doneFlag) {

//TODO: print list?
int imSad = 0;
struct memoryBlock* currNode = head;
printf("Current list information:\n");
while (!imSad) {
    printf("\t");
    printBlockInfo(currNode);
    if (currNode->next == NULL) {
        imSad = 1;
    }else currNode = currNode->next;
}

        //get user input
        printf("Allocator > ");
        chars = getline(&buf, &len, stdin);

        //case for exiting
        if (strncmp(buf, "X", 1) == 0) {
            doneFlag = 1;
            continue;
        }

        //case for requesting memory, check first 2 chars of input
        if (strncmp(buf, "RQ", 2) == 0 || strncmp(buf, "rq", 2) == 0) {
            //separate and validate input
            char *tmp = strtok(buf, " ");
            char *procID = strtok(NULL, " ");
            int size = atoi(strtok(NULL, " "));
            char *algorithm = strtok(NULL, " ");
            //remove \n from end of line
            algorithm[strlen(algorithm)-1] = '\0';

            if (procID == NULL || size < 1 || algorithm == NULL) {
                printf("ERROR: The input was not correct. Please reference the README for formatting.\n");
                continue;
            }
            if (strncmp(procID, "P", 1) != 0) {
                printf("ERROR: Please use process format of P<process number>\n");
                continue;
            }
            if (size <= 0) {
                printf("ERROR: Amount of memory requested must be a positive integer\n");
                continue;
            }

            //utilize the correct insertion algorithm
            struct memoryBlock* block = NULL;
            if (strcmp(algorithm, "F") == 0) {
                block = firstFit(procID, size);
            } else if (strcmp(algorithm, "B") == 0) {
                block = bestFit(procID, size);
            } else if (strcmp(algorithm, "W") == 0) {
                block = worstFit(procID, size);
            } else {
                printf("No algorithm matched with code: %s. Try F, B, or W.\n", algorithm);
                continue;
            }

            printf("New memory block created with ID: %s\n", block->id);

            //validate inserted information
            if (block != NULL) {
                printBlockInfo(block);
            }else {
                printf("Memory allocation failed\n");
                continue;
            }

        //case to release memory with the RL command
        }else if (strncmp(buf, "RL", 2) == 0) {
            //separate values 
            char* tmp = strtok(buf, " ");
            char* procID = strtok(NULL, " ");
            if (strncmp(procID, "P", 1) != 0) {
                printf("ERROR: Please use process format of P<process number>\n");
                continue;
            }
            int nodesReleased = releaseProcess(procID);
            if (nodesReleased > 0) {
                printf("%d processes with ID %s have successfully been released\n", nodesReleased, procID);
            } else printf("ERROR: No process with ID %s was found, could not release.\n", procID);

        //case to compact all of the memory
        } else if (strncmp(buf, "C", 1) == 0 ) {
            if (compact() == 0) {
                printf("Memory has been successfully compated\n");
            }else printf("Memory not compacted. Is there only one node?\n");
        
        //case to print the status of the memory
        } else if (strncmp(buf, "STAT", 4) == 0) {
            getStatus();
        }
    }
    
}

//util function to print entire linked list information
void getStatus() {
    struct memoryBlock* currNode = head;
    int endOfList = 0;
    while (!endOfList) {
        printBlockInfo(currNode);
        if(currNode->next == NULL) {
            endOfList = 1;
        } else currNode = currNode->next;
    }
}

//compact empty nodes
int compact() {
    struct memoryBlock* currNode = head;
    struct memoryBlock* nextNode = head->next;
    struct memoryBlock* prevNode = NULL;
    int swapped = 0;

    //only one node
    if (nextNode == NULL) {
        return 1;
    }
    while (1) {
        //check if next node is a gap
        if (strncmp(currNode->id, gapName, strlen(gapName)) != 0 && strncmp(nextNode->id, gapName, strlen(gapName)) == 0) {
            currNode = swap(currNode, nextNode, prevNode);
            nextNode = currNode->next;
            swapped = 1;
        }
        if (nextNode->next != NULL ) {
            prevNode = currNode;
            currNode = nextNode;
            nextNode = nextNode->next;
        //check if swap was made and repeat until no swaps
        } else if  (swapped) {
            swapped = 0;
            prevNode = NULL;
            currNode = head;
            nextNode = head->next;
        }else {
            releaseProcess(gapName);
            break;
        }
    }
    return 0;
}

//util function to swap nodes
struct memoryBlock* swap(struct memoryBlock* firstNode, struct memoryBlock* nextNode, struct memoryBlock* prevNode) {
    int firstSize = getSize(firstNode);
    int nextSize = getSize(nextNode);

    //update end locations
    firstNode->endLocation = nextNode->endLocation;
    nextNode->endLocation = firstNode->startLocation + nextSize;
    //update start locations
    nextNode->startLocation = firstNode->startLocation;
    firstNode->startLocation = firstNode->endLocation - firstSize;
    //udpate next nodes
    firstNode->next = nextNode->next;
    nextNode->next = firstNode;
    //check if at the start of list
    if (prevNode != NULL) {
        prevNode->next = nextNode;
    }else head = nextNode;

    return nextNode;
}

//util function to release a node from the list
int releaseProcess(char *id) {
    struct memoryBlock* currNode = head;
    struct memoryBlock* prevNode = NULL;
    int nodesFound = 0;

    printf("Releasing processes with ID: %s\n", id);

    while (1) {
        if (strncmp(currNode->id, id, strlen(id)) == 0) {
            currNode->id = gapName;
            currNode = mergeGapNodes(currNode, prevNode);
            nodesFound++;
        }
        if (currNode->next != NULL) {
            prevNode = currNode;
            currNode = currNode->next;
        }else break;
    }
    return nodesFound;
}

//merge 2 nodes based on process ID
struct memoryBlock* mergeGapNodes(struct memoryBlock* currNode, struct memoryBlock* prevNode) {
    struct memoryBlock* retNode = currNode;
    //merge the node with its previous node
    if (prevNode != NULL && strncmp(prevNode->id, currNode->id, strlen(currNode->id)) == 0) {
        prevNode->endLocation = currNode->endLocation;
        prevNode->next = currNode->next;
        free(currNode);
        retNode = prevNode;
    }
    //try to merge with the next node
    struct memoryBlock* nextNode = retNode->next;
    if (nextNode != NULL && strncmp(nextNode->id, retNode->id, strlen(retNode->id)) == 0 ) {
        retNode->endLocation = nextNode->endLocation;
        retNode->next = nextNode->next;
        free(nextNode);
    }
    return retNode;
}

//first fit memory allocation algorithm
struct memoryBlock* firstFit(char *id, int size) {
    struct memoryBlock *currNode = head;
    struct memoryBlock *newNode = NULL;

    while(1) {
        if (strncmp(currNode->id, gapName, strlen(gapName)) == 0) {
            int currSize = getSize(currNode);
            if (currSize >= size) {
                newNode =  insertNode(currNode, id, size);
                printf("Created process ID: %s\n", newNode->id);
                return newNode;
            }
        }
        //check to escape loop
        if (currNode->next == NULL) {
            break;
        } else currNode = currNode->next;
    }
    return NULL;
}

//best fit memory allocation algorithm
struct memoryBlock* bestFit(char* id, int size) {
    
    struct memoryBlock* currNode = head;
    struct memoryBlock* node;
    int bestFitSize = INT_MAX;
    int placeFound = 0;

    while (1) {
        if (strncmp(currNode->id, gapName, strlen(gapName)) == 0) {
            int currNodeSize = getSize(currNode);
            //update information when node would fit in size
            if (currNodeSize >= size && currNodeSize < bestFitSize) {
                node = currNode;
                bestFitSize = currNodeSize;
                placeFound = 1;
            }
        }
        if (currNode->next == NULL) {
            break;
        } else currNode = currNode->next;
    }
    //place the new node in the bestfit location
    struct memoryBlock* newNode = NULL;
    if (placeFound) {
        newNode = insertNode(node, id, size);
    }
    return newNode;
}

//worst fit memory allocation function
struct memoryBlock* worstFit(char* id, int size) {
    struct memoryBlock* currNode = head;
    struct memoryBlock* node;
    int worstFitSize = 0;
    int placeFound = 0;

    while (1) {
        if (strncmp(currNode->id, gapName, strlen(gapName)) == 0) {
            int currNodeSize = getSize(currNode);
            //update information when node is worst fit
            if (currNodeSize >= size && currNodeSize > worstFitSize) {
                node = currNode;
                worstFitSize = currNodeSize;
                placeFound = 1;
            }
        }
        if (currNode->next != NULL) {
            currNode = currNode->next;
        }else break;
    }
    struct memoryBlock* newNode = NULL;
    if (placeFound) {
        newNode = insertNode(node, id, size);
    }
    return newNode;
}

//utility function to create a new node in the linked list
struct memoryBlock* insertNode(struct memoryBlock* node, char* idInput, int size) {
    if (getSize(node) == size) {
        printf("Inputting ID: %s\n", idInput);
        node->id = idInput;
        printf("ID saved as: %s\n", node->id);
        return node;
    } else {
        printf("Inputting ID: %s\n", idInput);
        struct memoryBlock* newNode = (struct memoryBlock*)malloc(sizeof(memoryBlock));
        newNode->id = idInput;
        newNode->startLocation = node->endLocation - size;
        newNode->endLocation = node->endLocation;
        newNode->next = node->next;
        //update other node
        node->endLocation = node->endLocation - size - 1;
        node->next = newNode;
        printf("ID saved as: %s\n", newNode->id);
        return newNode;
    }
}

//util function to print information about a node
void printBlockInfo(struct memoryBlock* node) {
    printf("\tNode Info: Addresses [%d:%d] Process %s\n", node->startLocation, node->endLocation, node->id);
}

//utility function to calculate the size of a node
int getSize(struct memoryBlock* nodeInput) {
    return nodeInput->endLocation - nodeInput->startLocation;
}

//create the head node of the linked list
void createHead(int startBlockSize) {
    head = (struct memoryBlock*) malloc(sizeof(memoryBlock));
    head->id = gapName;
    head->startLocation = 0;
    head->endLocation = startBlockSize - 1;
    head->next = NULL;
}

