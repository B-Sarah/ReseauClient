#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <rpc/xdr.h>

#include "time.h"

#include "server.h"
#include "game.h"
#include "configClient.h"

#define PORT 3000
#define MAX_MSG_SIZE 1024

XDR xdr_encode;
XDR xdr_decode;

Server server;

pthread_t readThread;

char sent[MAX_MSG_SIZE];
char received[MAX_MSG_SIZE];


int connectToServer(char* serverAddress);
int timeoutConnect(int timeout);
void disconnectFromServer();
void initConnection(char* serverAddress);

void startServerHandler();
void* receiveMessages(void*);

void sendMessage(int encodedSize);
int decodeMessage(Character* character, Player* player, Object* object );

void initXdr();

void encodePlayer(Player* player);
void encodeCharacter(Character* character);
void encodeObject(Object* object);

#endif
