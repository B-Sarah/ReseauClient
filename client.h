#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <rpc/xdr.h>

#include "game.h"
#include "configClient.h"

#define PORT 3000
#define MAX_MSG_SIZE 1024

typedef struct{
	int socket;
	struct sockaddr_in address;
	unsigned short port;
	struct hostent* host;
}Server;

void connectToServer(Server* server,char* serverAddress);


#endif
