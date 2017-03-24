#include "client.h"

int connectToServer(char* serverAddress){
    if(server.socket != 0) return -1;

    printf("Connexion en cours...\n");
    initConnection(serverAddress);

	// demande de connexion au serveur
	if(!timeoutConnect(5)){
        printf("Connexion echouee !\n\n");
        return -1;
	}
	game.isRunning = 1;
    initXdr();

	fflush(stdout);

    startServerHandler();
    return 0;
}

int timeoutConnect(int timeout) {
    fd_set fdset;
    struct timeval tv;

    int flags = fcntl(server.socket, F_GETFL, NULL);
    flags |= O_NONBLOCK;
    fcntl(server.socket, F_SETFL, flags);

    connect(server.socket, (struct sockaddr *)&server.address, sizeof(server.address));

    FD_ZERO(&fdset);
    FD_SET(server.socket, &fdset);
    tv.tv_sec = 10;             /* 10 second timeout */
    tv.tv_usec = 0;

    if (select(server.socket + 1, NULL, &fdset, NULL, &tv) == 1)
    {
        int so_error;
        socklen_t len = sizeof so_error;

        getsockopt(server.socket, SOL_SOCKET, SO_ERROR, &so_error, &len);

        flags = fcntl(server.socket, F_GETFL, NULL);
        flags &= ~O_NONBLOCK;
        fcntl(server.socket, F_SETFL, flags);
        if (so_error == 0) {

            return 1;
        }
    }
    close(server.socket);
    server.socket = 0;
    return 0;
}


int decodeMessage(Character* character, Player* player, Object* object )
{
    if(xdr_player(&xdr_decode,player)){

        return 2;
    }

    else if(xdr_character(&xdr_decode,character)){

        return 3;
    }

     else if(xdr_object(&xdr_decode, object)){

        return 4;
    }

    else return -1;

}

void startServerHandler(){
    int pthread_return;

	//creation de thread d'acceptation de clients
	pthread_return = pthread_create(&readThread, NULL, receiveMessages, NULL);

	if(pthread_return){
		printf("ERROR; return code from pthread_create() is %d\n", pthread_return);
		return;
	}
}


void* receiveMessages(void* arg){
    Player player;
    Character character;
    Object object;

    while (game.isRunning){
        int len;
        memset(received, '\0',MAX_MSG_SIZE);
        if((len = read(server.socket, received, MAX_MSG_SIZE)) < 0){
            perror("read");
        }
        if(len == 0){
            hasBeenDeconected();
            break;
        }
        //printf("lu : %d\n", len);

        int action = decodeMessage(&character, &player, &object);

        switch(action){
        case 2:
            updatePlayer(&player);
            break;
        case 3:
            updateCharacter(&character);
            break;
        case 4:
            updateObject(&object);
            break;
        default:
            printf("Error occured while decoding message \n");

        }
        memset(received, '\0',MAX_MSG_SIZE);

    }
    pthread_exit(NULL);
}


void sendMessage( int encodedSize){
/*envoi du message contenant le player encode*/
    printf("Message envoyé : %s\n", sent);
	if(send(server.socket, sent,encodedSize, 0) != encodedSize){
		perror("write");
	}
}


void encodePlayer(Player* player){
    memset(sent, '\0',MAX_MSG_SIZE);

    xdr_setpos(&xdr_encode, 0);
    if(xdr_player(&xdr_encode, player)){
        int encodedSize = xdr_getpos(&xdr_encode);
        sendMessage(encodedSize);
    }
    else{
        printf("Erreur d'envoi de la trame joueur! \n");
    }




}

void encodeCharacter(Character* character){
    memset(sent, '\0',MAX_MSG_SIZE);

    xdr_setpos(&xdr_encode, 0);
    if(xdr_character(&xdr_encode, character)){
        int encodedSize = xdr_getpos(&xdr_encode);
        sendMessage(encodedSize);
    }
    else{
        printf("Erreur d'envoi de la trame personnage! \n");
    }
}


void encodeObject(Object* object){
    memset(sent, '\0',MAX_MSG_SIZE);

    if(xdr_object(&xdr_encode, object)){
        int encodedSize = xdr_getpos(&xdr_encode);
        sendMessage(encodedSize);
    }
    else{
        printf("Erreur d'envoi de la trame objet-jeu! \n");
    }
}



void initXdr(){
	/*creation des flots */
	xdrmem_create(&xdr_encode,sent, MAX_MSG_SIZE, XDR_ENCODE);
	xdrmem_create(&xdr_decode,received, MAX_MSG_SIZE, XDR_DECODE);

}



void initConnection(char* serverAddress){

    memset(&(server.address), '\0', sizeof(server.address));

	// creation de la socket locale
	if((server.socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(1);
	}

	// recuperation de l'adresse ip du serveur
	if((server.host = gethostbyname(serverAddress)) == NULL){
		perror("gethostbyname");
		exit(2);
	}

	// preparation de l'adresse du serveur
	server.port = (unsigned short)PORT;
	server.address.sin_family = AF_INET;
	server.address.sin_port = htons(server.port);
	bcopy(server.host->h_addr, &(server.address.sin_addr), server.host->h_length);

	//printf("Connexion en cours...\n");
	//fflush(stdout);

}

void disconnectFromServer(){
    game.isRunning = 0;
    if(server.socket == 0) return;
    /*memset(sent, '\0',MAX_MSG_SIZE);
    strcpy(sent, "disconnect");
    sendMessage(strlen(sent));*/

    close(server.socket);
    server.socket = 0;

    pthread_cancel(readThread);
}


