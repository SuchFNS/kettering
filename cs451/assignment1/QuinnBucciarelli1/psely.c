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
#include <math.h>
#include <unistd.h>

//globals / statics / structs
struct Process {
    char s[5];
    int uid;
    int pid;
    char ppid[5];
    int pri;
    int ni;
    int rss;
    int sz;
    char wchan[20];
    char tty[10];
    char time[10];
    char cmd[50];
    int c;
};

#define MAJOR_OF(d) (((unsigned)(d)>>8u) & 0xfffu)
#define MINOR_OF(d) (((unsigned)(d)&0xffu) | (((unsigned)(d)&0xfff00000u)>>12u))

int readStat(int i, struct Process *list) {
    int column = 0;
    FILE *fptr;

    char line[100];
    //open /proc/i/stat
    char filename[50] = "/proc";
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

    //hard code 0 to c
    list[i].c = 0;

    char *buf;
    buf = strtok(line, " ");
    //add pid to process list
    list[i].pid = atoi(buf);
    //printf("%d\t", list[i].pid);
    //get command name and remove parentheses
    buf = strtok(NULL, " ");
    buf++[strlen(buf)-1] = 0;
    strcpy(list[i].cmd, buf);

    //get state of program
    strcpy(list[i].s, strtok(NULL, " "));

    //get ppid
    strcpy(list[i].ppid, strtok(NULL, " "));

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

    //get application time
    for (int j = 0; j < 7; j++) {
        buf = strtok(NULL, " ");
    }
    //divide by 100 from sysconf(_SC_CLK_TCK) getting clock ticks
    double ticks = (atof(buf) + atof(strtok(NULL, " "))) / sysconf(_SC_CLK_TCK);
    double hours, minutes, seconds;
    hours = ticks / 3600;
    minutes = (ticks - hours*3600) / 60;
    seconds = ticks - hours*3600 - minutes*60;
    sprintf(list[i].time, "%0.0f:%0.0f:%0.0f", hours, minutes, seconds);

    //get NI and PRI
    for(int j = 0; j < 3; j++) {
        buf = strtok(NULL, " ");
    }
    list[i].ni = atoi(strtok(NULL, " "));
    list[i].pri = list[i].ni + 80;

    fclose(fptr);
    return(0);
}

void readStatus(int i, struct Process *list) {
    FILE *fptr;
    char *buf;
    int rssFoundFlag= 0;

    char line[100];
    //open status
    char filename[50] = "/proc";
    sprintf(filename, "%s/%d/%s", filename, i, "status");
    fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("couldnt open file %s\n", filename);
    }
    buf = fgets(line, 100, fptr);
    if (buf == NULL) {
        printf("error reading info from %s\n", filename);
    }
    //read until UID label is found
    while(!(strstr(buf, "Uid:"))) {
        buf = fgets(line, 100, fptr);
    }
    //tokenize and get first thing
    buf = strtok(buf, "\t");
    list[i].uid = atoi(strtok(NULL, "\t"));

    fclose(fptr);
}

void readStatm(int i, struct Process *list) {
    FILE *fptr;
    char *buf;

    char line[100];
    //open status
    char filename[50] = "/proc";
    sprintf(filename, "%s/%d/%s", filename, i, "statm");
    fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("couldnt open file %s\n", filename);
    }
    buf = fgets(line, 100, fptr);
    if (buf == NULL) {
        printf("error reading info from %s\n", filename);
    }
    //tokenize the line to get size
    buf = strtok(line, " ");
    list[i].sz = atoi(buf);
    //tokenize the line to get resident size, *4 to adjust for kB
    buf = strtok(NULL, " ");
    list[i].rss = atoi(buf) * 4;

    fclose(fptr);
}
void readWchan(int i, struct Process *list) {
    FILE *fptr;
    char *buf;

    char line[100];
    //open status
    char filename[50] = "/proc";
    sprintf(filename, "%s/%d/%s", filename, i, "wchan");
    fptr = fopen(filename, "r");
    if (fptr == NULL) {
       printf("couldnt open file %s\n", filename);
    }
    buf = fgets(line, 100, fptr);
    if (buf == NULL) {
        printf("error reading info from %s\n", filename);
    }
    if (!strcmp(buf, "0")) {
        strcpy(list[i].wchan, "-");
    } else strcpy(list[i].wchan, buf);
}

void printEntry(int i, struct Process *list) {
    printf("%s\t%d\t%d\t%s\t", list[i].s, list[i].uid, list[i].pid, list[i].ppid);
    printf("%d\t%d\t%d\t%d\t", list[i].c, list[i].pri, list[i].ni, list[i].rss);
    printf("%d\t%s\t%s\t%s\t%s\n", list[i].sz, list[i].wchan, list[i].tty, list[i].time, list[i].cmd);
}

/*
    This is structured horribly, I am sorry for anyone that
    has to look at this. But I mean, most of it can be hard
    coded anyways. Should have used more functions for 
    the easy stuff and not just slapped my forehead at using
    an array of structs without thinking about how to print 
    the data within them.
*/
int main(int argc, char* argv[]) {

    struct Process processList[32768];

    //print header:
    printf("S\tUID\tPID\tPPID\tC\tPRI\tNI\tRSS\tSZ\tWCHAN\tTTY\tTIME\tCMD\n");

    //max PID number = 32768, search all possible
    //TODO: change loop to take all PIDs
    for(int i = 0; i <= 32768; i++) {
        if (readStat(i, processList) != 0){
            //no file found for PID i, skip to next
            continue;
        }
        readStatus(i, processList);
        readStatm(i, processList);
        readWchan(i, processList);
        printEntry(i, processList);
    }
}