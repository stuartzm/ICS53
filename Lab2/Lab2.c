#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define ARRAY_MAX 10
#define FAILURE -1

void getInput(char * file_name, int * array, int *length) {
	FILE *file;
	file = fopen(file_name, "r");
	char line[255];
	*length = 0;

	if (file) {
		while(fgets(line, sizeof(line), file) != NULL)
		{
		   char *p = strtok(line, " ");
		   while( p != NULL) {
				if ((*length + 1) > ARRAY_MAX) { //Length cannot exceed 10
					*length = FAILURE;
					break;
				} else {
					int d = atoi(p); /* Assuming you are entering valid integers else use `strtol()` */
					array[(*length)++] = d;
					p = strtok(NULL, " ");
			 	}	
		   }

		   break; //should only read one line
		}
	} else
		printf("File could not be opened.\n");
}

bool forkSearch(int * array, int search, int start, int end) {
	// printf("Searching: %d - %d\n", start, end);
	if(start >= end) { // search has come to an end
		if (array[end] == search) {
			printf("%d\n", end);
			return true;
		} else 
			return false;
		exit(0); //Process did not find the number to search for.
	} else {
		pid_t child = fork();
		if (child == 0) 
			return forkSearch(array, search, start, (start + end)/2);
		else
			return forkSearch(array, search, (start + end)/2 + 1, end);
	}
}

int main( int argc, char *argv[] ) {
	bool found;
	pid_t pid = getpid();
	//TODO
	// int fd;
 //    char * myfifo = "/tmp/myfifo";

 //    mkfifo(myfifo, 0666);

	if (argc < 3 || argc > 3)
		printf("Incorrect arguments.\n");
	else {
		int array[ARRAY_MAX];
		int length;
		getInput(argv[1], array, &length);
		if (length != FAILURE) {
			found = forkSearch(array, atoi(argv[2]), 0, length);
		} else
			printf("Array has more than 10 elements.\n-1\n");
	}
	while (wait(NULL) > 0) {}
	if (!found && getpid() == pid)
		printf("-1\n");
	return 0;
}