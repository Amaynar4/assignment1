all: hmds

hmds: hmds.c
	gcc -Wall -Werror -g -O0 -std=gnu11 -o hmds hmds.c -lhdb

clean:
	rm -f *.o *.a hmds
