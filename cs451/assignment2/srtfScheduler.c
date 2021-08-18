/*
*   By: Colin Quinn and Elena Bucciarelli
*   Assignment 2 srtfScheduler.c
*   
*   SRTF scheudler that creates and manages child processes
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void makeProcList(char* inputFile);
void timer();
void timerHandler();

typedef struct ProcInfo {
    int ID;
    int AT;
    int Burst;
    int State;
    int PID;
}   ProcInfo;

//globals
struct ProcInfo procs[10]; //array of processes. Max 10 based on assignment.
int numOfProcesses;
int currTime = 0;
int procsLeft = 1; //true
char *childFile;


void makeProcList(char* inputFile) {
    FILE *filename = fopen(inputFile, "r");
    char buf[1000];
    char *tok;
    int procIndex = 0;

    //read up to 10 processes based on assignment requirements
    while(fgets(buf, 1000, filename) != NULL && procIndex < 10) {
        tok = strtok(buf, "\n");
        //skip header of the file
        if (strcmp(tok, "PID AT BURST") >= 0) {
            continue;
        }
        char *linebuf;
        //get PID
        linebuf = strtok(tok, " ");
        procs[procIndex].ID = atoi(linebuf);
        //get AT
        linebuf = strtok(NULL, " ");
        procs[procIndex].AT = atoi(linebuf);
        //get Burst
        linebuf = strtok(NULL, " ");
        procs[procIndex].Burst = atoi(linebuf);

        procIndex++;      
    }
    //save the number of processes in list and close the file
    numOfProcesses = procIndex;
    fclose(filename);
}

//This has been taken from the assignment prompt. only edited to sleep every second.
void timer() {

    struct sigaction sa;
    /* Install timer_handler as the signal handler for SIGALRM. */
    memset (&sa, 0, sizeof (sa));
    sa.sa_handler = &timerHandler;
    sigaction(SIGALRM, &sa, NULL);


    struct itimerval timer;
    /* Install timer_handler as the signal handler for SIGALRM. */
    /* The timer goes off 1 second after installation of the timer. */
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec =0;
    /* ... and every 1 second after that. */
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec =0;
    /* Start a real timer. It counts down whenever this process is
     executing. */
    setitimer (ITIMER_REAL, &timer, NULL);
    while (procsLeft) {
        sleep(1);
    }
    //sleep again to allow final child to print its info
    sleep(1);
    printf("Scheduling is done, exiting\n");
    return;
}

void timerHandler() {
    static int currProc = -1;
    static int prevProc = -1;

    printf("\nScheduler: Current time: %d seconds\n", currTime);
    
    //Case for current process and maintaining its information
    if (currProc != -1) {
        //1 second of burst gets used
        procs[currProc].Burst = procs[currProc].Burst - 1;
        //check burst value, if 0 then we terminate the process
        if (procs[currProc].Burst <= 0) {
            printf("Scheduler: Terminating process %d\n", currProc);
            //kill process and process info
            kill(procs[currProc].PID, SIGTERM);
            procs[currProc].State = 2;
            currProc = -1;
            prevProc = -1;
        }
    }

    //check for any processes left
    for (int i = 0; i < numOfProcesses; i++) {
        if (procs[i].State < 2) {
           break;
        //found last process as complete, so return out of function
        }else if (i == numOfProcesses - 1) {
            procsLeft = 0;
            return;
        }
    }

    //check for any process that has now arrived with a lower burst
    for (int i = 0; i < numOfProcesses; i++) {
        //skip any processes that aren't scheduled yet or are already finished
        if(procs[i].AT > currTime || procs[i].State == 2)
			continue;
        //schedule a new process that has arrived at currTime
        if (procs[i].AT == currTime) {
            printf("Scheduler: New process %d arrived with a burst of %d seconds\n", i, procs[i].Burst);
        }
        //check if any bursts are lower than the current and schedule the lowest
        if(procs[i].AT <= currTime && (currProc == -1 || procs[i].Burst < procs[currProc].Burst))
			currProc = i;
    }

    //check for any change from the above schedulers
    if (prevProc != currProc) {
        //pause the previous process if new one has gotten scheduled
        if (prevProc != -1) {
            printf("Scheduler: Suspending Process %d with remaining time %d seconds\n", prevProc, procs[prevProc].Burst);
            kill(procs[prevProc].PID, SIGSTOP);
        }
        //update the previous process to the current process -> to be updated next
        prevProc = currProc;

        //update currProc
        if (procs[currProc].State == 0) {
            //create new process
            int newPID = fork();
            //handle newPID being a child process
            if (newPID == 0) {
                char executablePath[20] = "./";
                strcat(executablePath, childFile);
                char procString[5];
                char pidString[5];
                sprintf(procString, "%d", currProc);
                sprintf(pidString, "%d", getpid());
                execl("./prime.o", "./prime.o", procString, pidString, NULL);
                //invalid due to itoa being undefined?
                //execl(executablePath, executablePath, itoa(currProc), itoa(getpid()));
                return;   
               
            }else {
                procs[currProc].State = 1;
                procs[currProc].PID = newPID;
                printf("Scheduler: Process %d has burst %d seconds\n", currProc, procs[currProc].Burst);
            }
        }else {
            printf("Scheduler: Resuming process %d with remaining burst of %d seconds\n", currProc, procs[currProc].Burst);
            kill(procs[currProc].PID, SIGCONT);
        }
    }
    currTime++;
}

int main (int argc, char* argv[]) {
    if (argc != 3) {
        printf("Please include an input file in the command line arguments\n");
    }
    childFile = argv[2];
    if (!childFile) {
        printf("Please include a child process filename to execute. Ex: prime.o\n");
        return(0);
    }
    makeProcList(argv[1]);
    timer();
}