#include "client.h"


void connectToServer(Server* server,char* serverAddress){
	XDR xdr_encode, xdr_decode;
	char sent[MAX_MSG_SIZE] = {'\0'};
	char received[MAX_MSG_SIZE] = {'\0'};
	Player player;

	strcpy(player.name, "Dorwed");
	strcpy(player.password, "ifucanreadthis");

	/*creation des flots */
	xdrmem_create(&xdr_encode,sent, MAX_MSG_SIZE, XDR_ENCODE);
	xdrmem_create(&xdr_decode,received, MAX_MSG_SIZE, XDR_DECODE);

	memset(&server->address, '\0', sizeof(server->address));
	// creation de la socket locale
	if((server->socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(1);
	}

	// recuperation de l'adresse ip du serveur
	if((server->host = gethostbyname(serverAddress)) == NULL){
		perror("gethostbyname");
		exit(2);
	}

	// preparation de l'adresse du serveur
	server->port = (unsigned short)PORT;

	server->address.sin_family = AF_INET;
	server->address.sin_port = htons(server->port);
	bcopy(server->host->h_addr, &(server->address).sin_addr, server->host->h_length);

	printf("Connexion en cours...\n");
	fflush(stdout);

	// demande de connexion au serveur
	if(connect(server->socket, (struct sockaddr*)(&(server->address)), sizeof(server->address)) == -1){
		perror("connect");
		exit(3);
	}

	printf("Connexion acceptee\n");
	fflush(stdout);

	/*encodage du player*/
	if(xdr_player(&xdr_encode, &player) == FALSE){
		printf("fail to encode \n");
		fflush(stdout);
	}
	/*
	char machaine[80];
	strcpy(machaine, "hello world");
	char* pt = machaine;
	*/
	//int posBef = xdr_getpos(&xdr_encode);
	//printf("Pos before %d\n", posBef);
	/*
	if(xdr_string(&xdr_encode,&pt, 80) == FALSE){
		printf("fail to encode \n");
		fflush(stdout);
	}*/
	int encodedSize = xdr_getpos(&xdr_encode);
	printf("Encoded %d characters\n", encodedSize);

	/*printf("message to send \"%s\"\n", sent);
	printf("first charac \"%c\" : %d\n", sent[0], sent[0]);
	printf("scnd charac \"%c\" : %d\n", sent[1], sent[1]);
	printf("last charac \"%c\" : %d\n", sent[MAX_MSG_SIZE], sent[MAX_MSG_SIZE]);
	fflush(stdout);
	*/

	/*envoi du message contenant le player encode*/
	if(send(server->socket, sent, encodedSize, 0) != encodedSize){
		perror("write");
	}

	/*printf("message has been sent \"%X\"\n", sent[3]);
	fflush(stdout);*/
}
/* xdr_Player */
bool_t xdr_player(XDR* pt_xdr, Player* player){
	char* pName = player->name;
	char* pPwd = player->password;
	char** ppName = &pName;
	char** ppPwd = &pPwd;

	return(xdr_string(pt_xdr, ppName, 30) &&
			xdr_string(pt_xdr, ppPwd, 20));

}

/* xdr_Character */

bool_t xdr_Charcter(XDR* pt_xdr, Character* character){
	char* pPseudo = character->pseudo;
	char** ppPseudo = &pPseudo;
	char skin = character->skin;
	char* pSkin = &skin;
	int* hp = &character->hp;
	int* x = &character->x;
	int* y = &character->y;

	return(xdr_string(pt_xdr, ppPseudo, 30) &&
			xdr_char(pt_xdr, pSkin) &&
			xdr_int(pt_xdr, hp) &&
			xdr_int(pt_xdr, x) &&
			xdr_int(pt_xdr, y));

}

/* xdr_Tile */

bool_t xdr_Tile(XDR* pt_xdr, Tile* tile){
	return 0;

}

/* xdr_Map */
/*
bool_t xdr_player(XDR* pt_xdr, Player* player){
	char* pName = player->name;
	char* pPwd = player->password;
	char** ppName = &pName;
	char** ppPwd = &pPwd;
Tile tiles[][];
	int width;
	int height;

	return(xdr_string(pt_xdr, ppName, 30) &&
			xdr_string(pt_xdr, ppPwd, 20));

}*/


