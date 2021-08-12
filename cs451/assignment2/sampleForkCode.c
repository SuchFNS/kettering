#include <stdio.h>
#include <stdlib.h>

int main(){ 

    int child_pid;

 
    int child_num = 1;
 
    char* argv[3];
    argv[0] ="./sample_prime.o";
    argv[1] ="child_num";
    argv[2] =NULL;

    child_pid = fork();
    if (child_pid==0){
        execlp("./sample_prime.o", argv[0],argv[1],argv[2]);
    } 
    else{
        waitpid(child_pid,NULL,0);
        printf("child finished");
   } 
}
