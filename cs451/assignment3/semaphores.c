/*
By Colin Quinn and Elena Bucciarelli
Operating Systems Assignment 3: Semaphores

Create groups assigning the game, a number, and the number
of games left for that group to play.
Claim dice required for the game.
Create thread function that forces game to wait between 0-10 seconds.
Return dice used and rejoin the queue.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

struct Game{
    char* name;
    int numDiceUsed;
};
struct Group {
    int id;
    struct Game gameGroup;
};

//constants
#define numberOfTables 8
#define numberOfGames 5

//globals
int diceAvailable = 8;
int diceInHand = 0;
int groupsDone = 0;

//semaphores to keep data synchronized
sem_t diceUpdater;
sem_t deskUpdater;
sem_t deskStatus;

//prototypes
void *groupTask (void *input);
void makeGroupTasks (pthread_t deskThread);
void *deskManagerTask (void *numDice);


void *deskManagerTask (void *numDice) {

    //make temp var for number of available dice and value of desk semaphore
    int prevDiceAvailable = *(int *)numDice;
    int deskVal = 0;

    //output number of dice and wait for a group by locking deskUpdater
    printf("\nDesk: Desk starting with %d dice available.\n\n", prevDiceAvailable);
    sem_wait(&deskUpdater);
    //continue until all groups are done 
    while(groupsDone < numberOfTables) {
        //check value of deskStatus to make sure desk is opened
        sem_getvalue(&deskUpdater, &deskVal);
        if (deskVal == 0) {
            //alter amount of dice available by the amount given/taken
            diceAvailable += diceInHand;
            if (diceInHand != 0) {
                printf("\n\tDesk: There are %d dice available\n\n", diceAvailable);
            }
            //amount of dice has been updated, reset inHand value
            diceInHand = 0;
            sem_post(&deskUpdater);
        }
        //unlock deskStatus
        sem_post(&deskStatus);
    }
    printf("\nDesk: The line is gone, closing desk...\n");
}

void makeGroupTasks (pthread_t deskThreadID) {

    struct Group groupList[numberOfTables];
    pthread_t threadid[numberOfTables];
    //this sucked to type and is a horrible way to do it, but everything else gave a segfault...
    //backgammon groups
    groupList[0].id = 0;
    groupList[0].gameGroup.name = "Backgammon";
    groupList[0].gameGroup.numDiceUsed = 4;
    groupList[1].id = 1;
    groupList[1].gameGroup.name = "Backgammon";
    groupList[1].gameGroup.numDiceUsed = 4;
    //risk groups
    groupList[2].id = 2;
    groupList[2].gameGroup.name = "Risk";
    groupList[2].gameGroup.numDiceUsed = 5;
    groupList[3].id = 3;
    groupList[3].gameGroup.name = "Risk";
    groupList[3].gameGroup.numDiceUsed = 5;
    //monopoly groups
    groupList[4].id = 4;
    groupList[4].gameGroup.name = "Monopoly";
    groupList[4].gameGroup.numDiceUsed = 2;
    groupList[5].id = 5;
    groupList[5].gameGroup.name = "Monopoly";
    groupList[5].gameGroup.numDiceUsed = 2;
    //pictionary groups
    groupList[6].id = 6;
    groupList[6].gameGroup.name = "Pictionary";
    groupList[6].gameGroup.numDiceUsed = 1;
    groupList[7].id = 7;
    groupList[7].gameGroup.name = "Pictionary";
    groupList[7].gameGroup.numDiceUsed = 1;

    for (int i = 0; i < numberOfTables; i++) {
        pthread_create(&threadid[i], NULL, &groupTask, (void *)&groupList[i]);
    }
    //attach desk thread to new threads made here
    pthread_join(deskThreadID, NULL);
    for (int i = 0; i < numberOfTables; i++) {
        //bind the new group thread to original thread
        pthread_join(threadid[i], NULL);
    }
}

void *groupTask (void *input) {

    struct Group inputGroup = *(struct Group*) input;
    sem_wait(&deskStatus);
    //loop for each game the group should play
    for (int i = 1; i <= numberOfGames; i++) {
        printf("Group %d: Requested %d dice for %s\n", inputGroup.id, inputGroup.gameGroup.numDiceUsed, inputGroup.gameGroup.name);

        //update dice count
        int diceAvailableFlag = 0;
        while (!diceAvailableFlag) {
            if (diceAvailable >= inputGroup.gameGroup.numDiceUsed && diceInHand == 0) {
                //lock diceUpdater 
                sem_wait(&diceUpdater);
                //update dice
                if (diceAvailable >= inputGroup.gameGroup.numDiceUsed) {
                    diceInHand -= inputGroup.gameGroup.numDiceUsed;
                    sem_wait(&deskUpdater);

                    //exit loop for next in queue
                    diceAvailableFlag = 1;
                }
                //unlock diceUpdater
                sem_post(&diceUpdater);
            }
        }

        //sleep for a random duration
        printf("Group %d: Started game %d of %s\n", inputGroup.id, i, inputGroup.gameGroup.name);
        sleep(rand() % (10 + 1));

        //game is done, lock semaphore and return the dice
        sem_wait(&diceUpdater);
        diceInHand += inputGroup.gameGroup.numDiceUsed;
        sem_wait(&deskUpdater);

        //display group status udpate and unlock diceUpdater
        printf("Group %d: We finished game %d of %s\n\tReturning %d dice.\n", inputGroup.id, i, inputGroup.gameGroup.name, inputGroup.gameGroup.numDiceUsed);
        sem_post(&diceUpdater);
    }
    printf("\nAll games done for group %d\n", inputGroup.id);
    groupsDone++;
}


int main(int argc, char* argv[]) {

    srand(time(NULL));
    //create semaphores
    sem_init(&diceUpdater, 0, 1);
    sem_init(&deskUpdater, 0, 1);
    sem_init(&deskStatus, 0, -1);

    //create desk management thread and task
    pthread_t deskThread;
    pthread_create(&deskThread, NULL, &deskManagerTask, (void *)&diceAvailable);

    //make the groups for each game
    makeGroupTasks(deskThread);

}