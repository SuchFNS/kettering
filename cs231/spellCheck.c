/*
Colin Quinn
Lab 4: CS 231
Use pipes and stdin/stdout redirection to spell check
a file of words against a dictionary list of words
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <signal.h>

int pid_id[4];

int main(int argc, char **argv){
	
	//list of args to pass through each pipe
	char *args[3];
	args[0] = "./lex.out";
	args[1] = argv[1];
	args[2] = NULL;
	
	char *sort[2];
	sort[0] = "sort";
	sort[1] = NULL;
	
	char *uniq[3];
	uniq[0] = "uniq";
	uniq[1] = "-i";
	uniq[2] = NULL;
	
	char *comp[3];
	comp[0] = "./compare.out";
	comp[1] = argv[2];
	comp[2] = NULL;	

	int count = 0;

	//creates the pipes needed
	int pi[2];
	int pi2[2];
	int pi3[2];
	
	//reap info from children
	signal(SIGCHLD, SIG_IGN);
	
	//open first pipe
	pipe(pi);
	
	//create the first child by fork() to lex.out
	if ((pid_id[0] = fork()) == 0){
		close(pi[0]);
		dup2(pi[1], STDOUT_FILENO);
		
		close(pi[1]);
		execvp("./lex.out", args);
	}
	//open second pipe
	pipe(pi2);
	
	//fork output from lex.out to sort function
	if((pid_id[1] = fork()) == 0){
		close(pi[1]);
		dup2(pi[0], STDIN_FILENO);
		close(pi[0]);
		
		close(pi2[0]);
		dup2(pi2[1], STDOUT_FILENO);
		close(pi2[1]);
		execvp(sort[0], sort);
	}
	//close pipe 1
	close(pi[0]);
	close(pi[1]);
	
	//open third pipe
	pipe(pi3);
	
	//fork output from sort to uniq
	if((pid_id[2] = fork()) == 0){
		close(pi2[1]);
		dup2(pi2[0], STDIN_FILENO);
		close(pi2[0]);
		
		close(pi3[0]);
		dup2(pi3[1], STDOUT_FILENO);
		close(pi3[1]);
	
		execvp(uniq[0], uniq);
	}
	//close pipe 2
	close(pi2[0]);
	close(pi2[1]);
	
	//fork output from uniq to compare.out to print to console
	if((pid_id[3] = fork()) == 0){
		close(pi3[1]);
		dup2(pi3[0], STDIN_FILENO);
		close(pi3[0]);
		
		execvp("./compare.out", comp);
	}
	//close pipe 3
	close(pi3[0]);
	close(pi3[1]);

    while(count < 4);

}

