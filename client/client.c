#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include "crcChecks.h"
#include "zlib.h"

int main (int argc, char **argv){

if (argv[1] == NULL || argv[2] == NULL){

	printf("\nArguments are NULL exiting.\n");
	exit(EXIT_FAILURE);

}//arguments provided were either both NULL or one was NULL

if (opendir(argv[1]) == NULL){

	printf("\nThe path supplied was invalid, exiting the program\n");
	exit(EXIT_FAILURE);

}//the path was invalid or empty 

printf("\nMain is running.\n");

char *cwd = NULL; //cwd will hold the directory that the user has supplied

cwd = argv[1];//grab the users path argument

printf("\ncwd is now : %s\n",cwd);

crcChecks(cwd); //call for the crc checksum function 

printf("\nNothing happened \n");

}//call the crcChecks function, sending the users supplied directory path, stored in cwd 

