#include <stdlib.h>
#include "hdb.h"
#include "list.c"

hdb_connection* hdb_connect(const char* server) {
  // Connect to the Redis server.
  // See https://github.com/redis/hiredis/blob/master/examples/example.c
  //
  // Cast the redisContext to an hdb_connection.
  // See the definition of hdb_connection in hdb.h -- notice that it's
  // just a typedef of void* (i.e. an alias of void*).
  //
  // Why are we doing this?  To hide our implementation details from
  // any users of the library.  We want to be able to change our
  // implementation at any time without affecting external code.
  // We don't want external users of the code to know we're using
  // Redis, so that, if we decided to switch to another data store
  // in the future, we could make the change internally, and no
  // external code would break.
  //
  // To avoid a compiler warning when casting the redisContext to
  // an hdb_connection, you may find the following line helpful
  // (don't be scared):
  // return *(hdb_connection**)&context;

    redisContext *c = redisConnect(server, 6379);

    checkConnection(c);

return *(c**)&context;

}//hdb_connect

void hdb_disconnect(hdb_connection* con) {
  // "Disconnect" from the Redis server (i.e. free the Redis context)
  // See https://github.com/redis/hiredis/blob/master/examples/example.c

   redisContext *c = con;

   checkConnection(c);

   redisFree(c);
   redisFree(con);

}

void hdb_store_file(hdb_connection* con, hdb_record* record) {
  // Store the specified record in the Redis server.  There are many ways to
  // do this with Redis.  Whichever way you choose, the checksum should be
  // associated with the file, and the file should be associated with the user.
  //
  // Hint: look up the HSET command.
  //
  // See https://github.com/redis/hiredis/blob/master/examples/example.c for
  // an example of how to execute it on the Redis server

   checkConnection(con);

   if (isEmpty()){

     makeList(record->username, record->filename, record->checksum);

     redisCommand(con,"HSET %s %s", "%s",record->username, record->filename, record->checksum);

   }//if the list has not been constructed or if the list is just empty 
   else{

     addToList(record->username, record->filename, record->checksum);

     redisCommand(con, "HSET %s %s", "%s", record->username, record->filename, record->checksum);

   }//else add a file like normal 

}

int hdb_remove_file(hdb_connection* con, const char* username, const char* filename) {
  // Remove the specified file record from the Redis server.

   checkConnection(con);

   char *chksum = redisCommand("HGET %s %s", username, filename);

   struct hdb_record requestRemove = NULL;

   requestRemove->username = username;
   requestRemove->filename = filename;
   requestRemove->checksum = chksum; 
   requestRemove->next = NULL;

   return removeFromList(requestRemove);

}

char* hdb_file_checksum(hdb_connection* con, const char* username, const char* filename) {
  // If the specified file exists in the Redis server, return its checksum.
  // Otherwise, return NULL.

  checkConnection(con);

  char *chksumFound = NULL;

  int reply = NULL;

  reply = redisCommand(con, "HEXISTS %s %s",username, filename);

  if (reply){

     char *request = redisCommand(con, "HGET %s %s", username, filename);

     if (request != NULL){

        return request; 

     }//null was not returned, return the checksum

     else{

       free(reply);
       free(request); 

       return NULL;

     }

  }//the record exists get the checksum 

  free (request);
  free (reply);

  return NULL;// the checksum was not in the database so return NULL

}

int hdb_file_count(hdb_connection* con, const char* username) {
  // Return a count of the user's files stored in the Redis server.

  checkConnection(con);

  return numRecords(username);

}

bool hdb_user_exists(hdb_connection* con, const char* username) {
  // Return a Boolean value indicating whether or not the user exists in
  // the Redis server (i.e. whether or not he/she has files stored).

  checkConnection(con);

  return nameInDB(username);

}

bool hdb_file_exists(hdb_connection* con, const char* username, const char* filename) {
  // Return a Boolean value indicating whether or not the file exists in
  // the Redis server.

  checkConnection(con);

  return fileInDB(username, filename); 

}

hdb_record* hdb_user_files(hdb_connection* con, const char* username) {
  // Return a linked list of all the user's file records from the Redis
  // server.  See the hdb_record struct in hdb.h  -- notice that it 
  // already has a pointer 'next', allowing you to set up a linked list
  // quite easily.
  //
  // If the user has no files stored in the server, return NULL.

  checkConnection(con);

  if (!(nameInDB(username))){

   return NULL;//username was not found in the database

  }
  else{

    struct hdb_record *list = NULL;  
    struct hdb_record *next = NULL;
    struct hdb_record *tmp = NULL;

    char* fname = redisCommand(con, "HGET %s", username);//get the first filename
    //assocaited with the username 

    if (fname == NULL){return NULL;}

      else{

       list = getRecord(username, fname);
       next = list;
       tmp = list;

         while (!(getNextMatch(fname) == NULL)){

          fname = getNextMatch(fname);
          next = getRecord(username, fname);

          if (!(next == NULL)){

            tmp->next = next;

          }
          else{return list;}

         }//while 

    }//else there is atleast one file to put in the list

  }//else

}

void hdb_free_result(hdb_record* record) {
  // Free up the memory in a linked list allocated by hdb_user_files().

  checkConnection(con);  

}

int hdb_delete_user(hdb_connection* con, const char* username) {
  // Delete the user and all of his/her file records from the Redis server.

  checkConnection(con);

  return -99; // Remove me
}
