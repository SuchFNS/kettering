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
    char *cmd;
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
    column++;
    //add pid to process list
    list[i].pid = atoi(buf);
    printf("%d\t", list[i].pid);
    //get command name and remove parentheses
    buf = strtok(NULL, " ");
    column++;
    buf++[strlen(buf)-1] = 0;
    list[i].cmd = buf;
    //printf("%s\t", list[i].cmd);

    //get state of program
    strcpy(list[i].s, strtok(NULL, " "));
    column++;
    //printf("%s\t", list[i].s);

    //get ppid
    strcpy(list[i].ppid, strtok(NULL, " "));
    column++;
    //printf("%s\t", list[i].ppid);

    //get tty
    for (int j = 0; j < 3; j++) {
        buf = strtok(NULL, " ");
        column++;
    }
    int tty_nr = atoi(buf);
    int major = MAJOR_OF(tty_nr);
    int minor = MINOR_OF(tty_nr);
    if (major == 4){
        sprintf(list[i].tty, "%s%d", "tty", minor);
    } else if (major == 136) {
        sprintf(list[i].tty, "%s%d", "pts", minor);
    } else strcpy(list[i].tty, "?");
    //printf("%s\t", list[i].tty);

    //get application time
    for (int j = 0; j < 7; j++) {
        buf = strtok(NULL, " ");
        column++;
    }
    //divide by 100 from sysconf(_SC_CLK_TCK) getting clock ticks
    double ticks = (atof(buf) + atof(strtok(NULL, " "))) / sysconf(_SC_CLK_TCK);
    column++;
    //TODO: convert ticks to hours, minutes, seconds
    //printf("ticks: %f\t", ticks);


    //get NI and PRI
    for(int j = 0; j < 3; j++) {
        buf = strtok(NULL, " ");
        column++;
    }
    list[i].ni = atoi(strtok(NULL, " "));
    column++;
    list[i].pri = list[i].ni + 80;
    //printf("pri: %d\tni: %d\t", list[i].pri, list[i].ni);

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
    printf("%s", buf);
    list[i].uid = atoi(strtok(NULL, "\t"));
    printf("%d\t", list[i].uid);

    //read until vmRSS is found
    //TODO: fix this
    /*
    while(!rssFoundFlag || buf == NULL) {
        printf("checking vmRSS: %s", buf);
        if (strstr(buf, "VmRSS:")){
            rssFoundFlag = 1;
            continue;
        }
        buf = fgets(line, 100, fptr);
    }
    if (rssFoundFlag) {
        //tokenize and get first thing
        buf = strtok(buf, "\t");
        printf("%s", buf);
        list[i].rss = atoi(strtok(NULL, "\t"));
        printf("%d", list[i].uid);
    }else list[i].rss = -1;
    */

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
    //tokenize the line
    buf = strtok(line, " ");
    list[i].sz = atoi(buf);
    //printf("%d", list[i].sz);

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
    strcpy(list[i].wchan, buf);
    //printf("%s", list[i].wchan);
}

void printEntry(int i, struct Process *list) {
    printf("\n");
    printf("%s\t%d\t%d\t%s\t%d\t%d\t%d\t\n", list[i].s, list[i].uid, \
            list[i].pid, list[i].ppid, list[i].c, list[i].pri, list[i].ni);
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
    printf("S\tUID\tPID\tPPID\tC\tPRI\tNI\tRSS\tSZ\tWCHAN\t\tTTY\tTIME\t\tCMD\n");

    //max PID number = 32768, search all possible
    //TODO: change loop to take all PIDs
    for(int i = 0; i <= 20; i++) {
        if (readStat(i, processList) != 0){
            //printf("no file found for pid %d\n", i);
            continue;
        }
        readStatus(i, processList);
        readStatm(i, processList);
        readWchan(i, processList);

        //printEntry(i, processList);
    }
}
