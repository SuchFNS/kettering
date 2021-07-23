/*
Program by: Colin Quinn, Elena Bucciarelli
Imitates the functions of the command <ps -ely>
by searching the /proc folder for system processes
*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

//globals / statics / structs
struct Process {
    char s[5];
    char uid[5];
    int pid;
    char ppid[5];
    char pri[5];
    char ni[5];
    char rss[5];
    char sz[5];
    char wchan[5];
    char tty[10];
    char time[10];
    char *cmd;
    char c;
};

#define MAJOR_OF(d) (((unsigned)(d)>>8u) & 0xfffu)
#define MINOR_OF(d) (((unsigned)(d)&0xffu) | (((unsigned)(d)&0xfff00000u)>>12u))

int readStat(int i, struct Process *list) {
    FILE *fptr;

    char line[100];
    //open stat first
    char filename[100] = "/proc";
    sprintf(filename, "%s/%d/%s", filename, i, "stat");
    fptr = fopen(filename, "r");
    if (fptr == NULL) {
       //printf("couldnt open file %s\n", filename);
       return(1);
    }
    if (fgets(line, 100, fptr) == NULL) {
        printf("error reading info from %s\n", filename);
        return(2);
    }

    char *buf;
    buf = strtok(line, " ");
    //add pid to process list
    list[i].pid = atoi(buf);
    printf("%d\t", list[i].pid);
    //get command name and remove parentheses
    buf = strtok(NULL, " ");
    buf++[strlen(buf)-1] = 0;
    list[i].cmd = buf;
    printf("%s\t", list[i].cmd);

    //get state of program
    strcpy(list[i].s, strtok(NULL, " "));
    printf("%s\t", list[i].s);

    //get ppid
    strcpy(list[i].ppid, strtok(NULL, " "));
    printf("%s\t", list[i].ppid);

    //get tty
    for (int j = 0; j < 3; j++) {
        buf = strtok(NULL, " ");
    }
    int tty_nr = atoi(buf);
    int major = MAJOR_OF(tty_nr);
    int minor = MINOR_OF(tty_nr);
    if (major == 4){
        sprintf(list[i].tty, "%s%d", "tty", minor);
    } else if (major == 136) {
        sprintf(list[i].tty, "%s%d", "pts", minor);
    } else strcpy(list[i].tty, "?");
    printf("%s\t", list[i].tty);

    //get application time
    for (int j = 0; j < 7; j++) {
        buf = strtok(NULL, " ");
    }
    int ticks = atoi(buf); //+ atoi(strtok(NULL, " "));
    printf("ticks: %d\n", ticks);

    fclose(fptr);
    return(0);
}


int main(int argc, char* argv[]) {

    struct Process processList[32768];

    //max PID number = 32768, search all possible
    //TODO: change loop to take all PIDs
    for(int i = 1450; i <= 1500; i++) {
        if (readStat(i, processList) != 0){
            //printf("no file found for pid %d\n", i);
            continue;
        }
    }


    /*
    use strtok to split input string (isnt needed elsewhere, shred it)
    pull all information from stat, then pull all from status, then statm and wchan.
    store all in strings and then sprintf to concatenate everything
    */

}
