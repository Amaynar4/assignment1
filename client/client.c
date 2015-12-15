#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <syslog.h>
#include <hdb.h>
#include <hfs.h>
#include <syslog.h>

int main(int argc, char** argv)
{

  int c;
  int verbose_flag = 0; 
  char* log_filename = NULL; 
  char* server_name = NULL;
  char* server_port = NULL; 
  char* server_root = NULL; 
  char* username = NULL;
  char* password = NULL; 
  char* log_file = logfile; 

  openlog(log_file, LOG_PID | LOF_NDELAY, LOG_USER); 

  while(1){

	static struct option long_options[]=
	{

	  {"server", required_argument, 0,'s'},
	  {"port", required_argument, 0, 'p'},
	  {"dir", required_argument, 0, 'd'},
	  {"verbose", no_argument, &verbose_flag, 1},
	  {0, 0, 0, 0}

	};

	int option_index = 0; 
	c = getopt_long(argc, argv, "spdv:", long_options, &option_index);

	if (c == -1)break;
	
	switch(c){

	  case 's' :
	  if (optarg == NULL){server_name = "localhost";}
	  else{
	    syslog(LOG_INFO, "servername option read");
	    server_name = optarg; 
	  }
	  break;
	
	  case 'p' : 
	  if (optarg == NULL) {server_port = "9000";}
	  else {
	    syslog(LOG_INFO, "serverport option read");
	    server_port = optarg;
	  }
	  break; 

	  case 'd' : 
	  if (optarg == NULL){server_root = "~/hooli";}
	  else {
	    syslog(LOG_INFO, "server root address option read");
	    server_root = optarg;
	  }
	  break;

	  case 'v' :
	  verbose_flag = true;    
	  break;

	} 

  } 
 
	if ((optind == argc - 2) && (argv[optind] != NULL)){

  	  username = argv[optind];
 	  ++optind;

	}//check for a username argument
	else {
	printf("invalid arguments");
	exit(EXIT_FAILURE);
	}

	if ((optind == argc - 1) && (argv[optind] != NULL)){

	  password = argv[optind];
	  ++optind;	

	}//check for a password argument
	else{
	printf ("invalid arguments");
	exit(EXIT_FAILURE);
	} 

	hdb_connection* connection = hdb_connect(server_name); 
	if (connection == NULL)
	{

	  printf("No connection.");
	  exit(EXIT_FAILURE); 

	}//check whether connnection went through 	

	

	char* auth = hdb_authenticate(connection, username, password);
	
	if (auth == NULL)
	{

	  syslog(LOG_ERR,"credentials wrong.");
	  exit(EXIT_FAILURE);

	}//check credentials with server 

	hfs_entry* clientList =  hfs_get_files (server_root); 
	hdb_record* serverList = hdb_user_files(connection, username);

	if (clientList == NULL){
	  syslog(LOG_ERR,"no client files");
	}
	if (serverList == NULL){
	syslog(LOG_ERR,"no server files");
	}

	int sequenceNum = 0; 

	hmdp_request* hmdp_req =  hmdp_create_auth_request(username, password);

	hdb_record* files = hdb_user_files(connection, username);

	typedef struct {
	int length;
	uint8_t buffer[UDP_MSS];
	} message;

	while (files != null){

		//create new message of type 1 to send to hfs with next seqnum
		message* msg = create_message();				
		//append  chunck of files to msg 		

		//invalid auth token gives an error
		if (connection == null){
			syslog(LOG_ERR, "connection lost");
			exit(EXIT_FAILURE);
		}
		//else send a data message containing file chunks
		else{
			
 		}

		//and wait for each  ACK

		//move to next file in struct
		files = files->next;

	}//do for each file needed to be transferred		

}

message* create_message(){
 return (message*)malloc(sizeof(message));
}
