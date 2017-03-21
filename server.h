#ifndef SERVER_H
#define SERVER_H


typedef struct{
	int socket;
	struct sockaddr_in address;
	unsigned short port;
	struct hostent* host;
}Server;

#endif // SERVER_H

