#include "client.h"

XDR xdr_encode;
XDR xdr_decode;

char sent[MAX_MSG_SIZE] = {'\0'};
char received[MAX_MSG_SIZE] = {'\0'};


void connectToServer(Server* server,char* serverAddress){

    initConnection(&server, serverAddress);

	// demande de connexion au serveur
	if(connect(server->socket, (struct sockaddr*)(&(server->address)), sizeof(server->address)) == -1){
		perror("connect");
		exit(3);
	}

	printf("Connexion acceptee\n");
	fflush(stdout);
	//int encodedSize = xdr_getpos(&xdr_encode);

}


int decodeMessage(char* serverMsg)
{



}

void initXdr(){
	/*creation des flots */
	xdrmem_create(&xdr_encode,sent, MAX_MSG_SIZE, XDR_ENCODE);
	xdrmem_create(&xdr_decode,received, MAX_MSG_SIZE, XDR_DECODE);

}

void sendMessage(Server* server, char* msg, int encodedSize){
/*envoi du message contenant le player encode*/
	if(send(server->socket, msg, encodedSize, 0) != encodedSize){
		perror("write");
	}
}


void initConnection(Server ** server, char* serverAddress){

    memset(&(*(server))->address, '\0', sizeof((* (server))->address));

	// creation de la socket locale
	if(((*(server))->socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(1);
	}

	// recuperation de l'adresse ip du serveur
	if(((*(server))->host = gethostbyname(serverAddress)) == NULL){
		perror("gethostbyname");
		exit(2);
	}

	// preparation de l'adresse du serveur
	(*(server))->port = (unsigned short)PORT;
	(*(server))->address.sin_family = AF_INET;
	(*(server))->address.sin_port = htons((*(server))->port);
	bcopy((*(server))->host->h_addr, &((*(server))->address).sin_addr, (*(server))->host->h_length);

	printf("Connexion en cours...\n");
	fflush(stdout);

}



