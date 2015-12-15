all: client

client: client.c
	gcc -I../hdb -Wall -Werror -g -O0 -std=gnu11 -o client client.c -lhdb -lhfs -lhmdp 

clean: 
	rm -f *.o *.a client
