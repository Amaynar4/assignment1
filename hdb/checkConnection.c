#include <unistd.h>
#include <hiredis/hiredis.h>

void checkConnection (redisContext connection){

  if (connection != NULL && connection->err){

     printf("Error in connecting to redis server : %s", connection->errstr);

  }//checks if connection is error free

}//checks that the users connection is still open and error free
