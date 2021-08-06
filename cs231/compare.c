/*
Colin Quinn
Lab 4: CS 231
Use pipes and stdin/stdout redirection to spell check
a file of words against a dictionary list of words
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>

const int MAX = 25;

/*
Empty string that is passed in as param
*/
void emptyStr(char *str){
	int i = 0;
	while (i < MAX){
		str[i] = '\0';
		i++;
	}
}

/*
Assuming each list is sorted, determine whether or 
not the words in the input file are spelled correctly
relying on ASCII values and determining if one is 
greater than the other
*/
int main(int argc, char **argv){
	
	char input[MAX];
	char dict[MAX];
	int difference;
	
	//initialize strings
	emptyStr(input);
	emptyStr(dict);
	
	//open dictionary file to read
	FILE * dictionary;
	if (dictionary = fopen(argv[2], "r")){

		fgets(input, MAX, stdin);
		fgets(dict, MAX, dictionary);

		while(1){
			difference = strncasecmp(dict, input, MAX);
//printf("%d\n", difference);
//printf("%s\t%s", input, dict);

			//if words are equal
			if (difference == 0){
				printf("Word is spelled correctly: %s", input);
				//if next word of either list is null then stop
				if (((fgets(input, MAX, stdin)) == NULL) || (((fgets(dict, MAX, dictionary)) == NULL))){
					break;
				}
			//if word is still less than value in dictionary
			}else if (difference < 0){
				//if at the end of dictionary, stop
				if ((fgets(dict, MAX, dictionary)) == NULL){
					break;
				}
			//if dictionary word is greater than word
			}else if (difference > 0){
				printf("Word is NOT spelled correctly: %s", input);
				//break if at the end of word list
				if ((fgets(input, MAX, stdin)) == NULL){
					break;
				}
			}
difference = 0;
//sleep(1);		
		}
		printf("done\n");

	//error statement for dictionary not being found
	}else printf("Error: Dictionary file not found");
	
	return 0;

}
