/*
By Colin Quinn and Elena Bucciarelli
Operating Systems Assignment 3: Semaphores

Create groups assigning the game, a number, and the number
of games left for that group to play.
Claim dice required for the game.
Create thread function that forces game to wait between 0-10 seconds.
Return dice used and rejoin the queue.
*/

#include <semaphore.h>

struct Group{
    char* game;
    int numDieRequired;
    int gamesLeft;
};

//globals
sem_t mutex;
int diceAvailable = 8;

int main(int argc, char* argv[]) {



}