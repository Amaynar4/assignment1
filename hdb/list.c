#include <"unistd">

//use this structure for the hooli database 
typedef struct hdb_record{

char *username;
char *filename;
char *checksum;
struct* hdb_record next;

}hdb_record;

//start and end nodes for the linked list
struct hdb_record end = NULL;
struct hdb_record start = NULL;

void makeList (char *uname, char *fname, char *chksum){

//A linked list is created to hold the  hooli data.
//The start and end addresses of the llinked list are always known 
//The start and end of the linked list when there is one record are equivalent

   end->username = uname;
   end->filename = fname;
   end->checksum = chksum;
   end->next = NULL;

   start = end; 

}//makeList

void addToList (char *uname, char *fname, char *chksum){

//Add a new node to the hooli database
//newNode is initialized with the new data 
//The end of the linked list points to this newNode
//The end of the list then becomes newNode so that more nodes can be added later 
//newNode is freed 

   struct hdb_record newNode = NULL;

   newNode->username = uname;
   newNode->filename = fname; 
   newNode->checksum = chksum;
   newNode->next = NULL;

   end->next = newNode; 

   end = newNode;

   free(newNode); 

}//addToList

int removeFromList(struct hdb_record target){

  struct hdb_record current = NULL;
  struct hdb_record previous = NULL; 

  if (!(isEmpty())){

    tmp = start; 

    if (tmp = target){

      start = NULL;
      end = NULL; 
   
      return 1;

    }//the first item in the list needs to be removed
    else{
     
      while (hasNext(tmp)){

        previous = tmp; 
	tmp = tmp->next; 

        if (tmp = target) {

           previous->next = tmp->next;
           return 1;

        }//remove the item 

      }//while the entire list has not been traversed 
    
     }//else the target may still be in the list 

  }//if the list is not empty 
  else {

    return 0;

  }//the list was empty 

  free(current);
  free(previous);

  return 0;

}//removeFromList

int isEmpty(){

if (start == NULL && end == NULL){return 1;}//the linked list is empty 
else {return 0;}//the linked list is not empty 

}//isEmpty

int hasNext(struct hdb_record target){

//if the target record points to another record return 1 

  if (!(target == NULL)){

    if (!(target->next == NULL)){return 1}//the target record points to another record 
    else {return 0;}//the target record does not point to another record  

  }//target is not null
  else{

    return 0;

  }//the null target does not point to another record in the list 

}//hasNext

int numRecords (const char* uname){

//scans through entire list counting the number of records belonging to a certain user

  int count = 0; 

  struct hdb_record tmp = NULL;

  tmp = start; 

  while(hasNext(tmp)){

    if (tmp->username = uname){count++;}//tmp's username field matches the name being 
    //searched for, increase count 

    tmp = tmp->next;//move tmp pointer to next record in list

  }//while the list has not been fully searched yet 

  if (tmp->username = uname){count++;}//check the last file in the list for a name match
 
  return count; 

}//numRecords

bool nameInDB(const char* uname){

  struct hdb_record tmp = NULL;//use tmp to traverse the list 

  tmp = start; //start at the beginning of the list  

  while (hasNext(tmp)){

    if (tmp->username = uname){return true;}//a record matching the search name has been found 

    tmp = tmp->next;//point to next record in the list 

  }//while the tmp pointer points to another record in the list 

  if (tmp->userame = uname){return true;}//check last entry in list 

  free(tmp);

  return false;//no name was found to match the search, return false 

}//nameInDB

bool fileInDB(const char* uname, const char* fname){

  struct hdb_record tmp = NULL;//use tmp to traverse the list 

  tmp = start; //start at the beginning of the list  

  while (hasNext(tmp)){

    if (tmp->username = uname && tmp->filename = fname){return true;}//a record matching the search has been found 

    tmp = tmp->next;//point to next record in the list 

  }//while the tmp pointer points to another record in the list 

  if (tmp->userame = uname && tmp->filename = fname){return true;}//check last entry in list 

  free(tmp);

  return false;//no record was found to match the search, return false 

}//fileInDB

char * getNextMatch(const char* uname, const char* fname){

 struct hdb_record tmp = NULL;//use tmp to traverse the list 

  tmp = start; //start at the beginning of the list  

  while (hasNext(tmp)){

    if (tmp->username = uname && tmp->filename = fname){

     tmp = tmp->next;

     return tmp->filename;

    }//match has been found
    else{

      tmp = tmp->next;

    }//keep searching  

  }//while the tmp pointer points to another record in the list 

  free(tmp);

  return NULL;//no record was found to match the search, return false 

}//getNextMatch

hdb_record * getRecord(const char* uname, const char* fname){

 struct hdb_record tmp = NULL;//use tmp to traverse the list 

  tmp = start; //start at the beginning of the list  

  while (hasNext(tmp)){

    if (tmp->username = uname && tmp->filename = fname){

     return tmp;//return the found record

    }//match has been found
    else{

      tmp = tmp->next;

    }//keep searching  

  }//while the tmp pointer points to another record in the list 

  if (tmp->username == uname&& tmp->filename == fname){return tmp;}//return the found record

  free(tmp);

  return NULL;//no record was found to match the search, return false 

}//getRecord
