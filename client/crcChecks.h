#ifndef CRCCHECKS_H
#define CRCCHECKS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include "zlib.h"

void crcChecks(char *path);//run the full file tree through a crc32 checksum 

#endif
