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

#include "server.h"
#include "game.h"
#include "configClient.h"

#define PORT 3000
#define MAX_MSG_SIZE 1024

XDR xdr_encode;
XDR xdr_decode;

char sent[MAX_MSG_SIZE];
char received[MAX_MSG_SIZE];


void connectToServer(Server* server,char* serverAddress);
void disconnectFromServer(Server* server);
void initConnection(Server** server, char* serverAddress);

void startServerHandler(Server* server);
void receiveMessages(void* server);

void sendMessage(Server* server, int encodedSize);
int decodeMessage(void** gameObject);

void initXdr();
void hasBeenDeconected();

void encodePlayer(Server* server, Player* player);
void encodeCharacter(Server* server, Character* character);
void encodeObject(Server* server, Object* object);

#endif
