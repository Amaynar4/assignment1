#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include "crcChecks.h"
#include "zlib.h"

void crcChecks (char *path){

  printf ("\nhello\n");

  DIR *pDir = NULL; // pointer to the supplied directory
  struct dirent *pEnt = NULL; //pointer to current entity in a directory

  pDir = opendir(path); //pDir points to the beginning of the supplied directory name
  FILE *f = fopen ("checkSums.txt", "w");

  if (pDir == NULL){

    printf("\n Directory could not be opened \n");
    exit (EXIT_FAILURE);

  }//if the directory could not be opened display this message and exit the program

  pEnt = readdir(pDir);

  do {

    if (pEnt == NULL){

      printf("\n No directory or file in the path, %s\n, pEnt");

    }//if the pEnt pointer is empty

    if (pEnt->d_type == DT_DIR){

      printf("\ndirectory found ... pEnt is : %s\n pEnt.d_name", pEnt, pEnt.d_name);
      crcChecks(pEnt);

    }//a directory was found inside the specified path, check for files inside this directory 

    else{

      if (strcmp(pEnt->d_name),(".") || strcmp(pEnt->d_name),("..")){

        //ignore these files 

      }//see if pEnt is a . or .. entity and ignore them 

      else{

        fprintf(f, "\n%s : %lu, \n",pEnt.d_name, crc32(0, (const void*)pEnt, strlen(pEnt)));
        printf("\nFile found : %s, checksum computed : %lu\n", pEnt.d_name, crc32(0, (const void*)pEnt, strlen(pEnt)));

        crcChecks(pEnt);

      }//all other discoverables are files that need to be crc32'ed and recorded in a txt file 

    }//all other discoverables are file types 
