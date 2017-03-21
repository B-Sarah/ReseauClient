#include "client.h"

void connectToServer(Server* server,char* serverAddress){

    initConnection(&server, serverAddress);

	// demande de connexion au serveur
	if(connect(server->socket, (struct sockaddr*)(&(server->address)), sizeof(server->address)) == -1){
		perror("connect");
		exit(3);
	}
    initXdr();

	printf("Connexion acceptee\n");
	fflush(stdout);


}


int decodeMessage(void** gameObject)
{
    if(xdr_player(&xdr_decode, *gameObject)){

        return 2;
    }

    else if(xdr_character(&xdr_decode, *gameObject)){

        return 3;
    }

     else if(xdr_object(&xdr_decode, *gameObject)){

        return 4;
    }

    else return -1;

}

void startServerHandler(Server* server){
    int pthread_return;
	pthread_t thread;

	//creation de thread d'acceptation de clients
	pthread_return = pthread_create(&thread, NULL, receiveMessages, (void*)(server));

	if(pthread_return){
		printf("ERROR; return code from pthread_create() is %d\n", pthread_return);
		return;
	}
}


void receiveMessages(void* _server){
    void* gameObject;
    Server* server = (Server*)_server;


    while (game.isRunning){
        int len;
        if((len = read(server->socket, received, MAX_MSG_SIZE)) < 0){
            perror("read");
        }
        if(len == 0){
            hasBeenDeconected();
            break;
        }
        printf("lu : %d\n", len);

        int action = decodeMessage(&gameObject);

        switch(action){
        case 2:
            updatePlayer((Player*)gameObject);
            printf("this is an update dude it worked !! %d\n",((Player*)gameObject)->logged);
            break;
        case 3:
            updateCharacter((Character*)gameObject);
            break;
        case 4:
            updateObject((Object*)gameObject);
            break;
        default:
            printf("Error occured while decoding message \n");

        }
        memset(received, '\0',MAX_MSG_SIZE);

    }
}

void hasBeenDeconected(){
    printf("Vous avez été déconnectée du serveur \n");
 }



void sendMessage(Server* server, int encodedSize){
/*envoi du message contenant le player encode*/
	if(send(server->socket, sent,encodedSize, 0) != encodedSize){
		perror("write");
	}
}


void encodePlayer(Server* server, Player* player){
    memset(sent, '\0',MAX_MSG_SIZE);

    if(xdr_player(&xdr_encode, player)){
        int encodedSize = xdr_getpos(&xdr_encode);
        sendMessage(server, encodedSize);
    }
    else{
        printf("Erreur d'envoi de la trame joueur! \n");
    }




}

void encodeCharacter(Server* server, Character* character){
    memset(sent, '\0',MAX_MSG_SIZE);

    if(xdr_character(&xdr_encode, character)){
        int encodedSize = xdr_getpos(&xdr_encode);
        sendMessage(server, encodedSize);
    }
    else{
        printf("Erreur d'envoi de la trame personnage! \n");
    }
}


void encodeObject(Server* server, Object* object){
    memset(sent, '\0',MAX_MSG_SIZE);

    if(xdr_object(&xdr_encode, object)){
        int encodedSize = xdr_getpos(&xdr_encode);
        sendMessage(server, encodedSize);
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

	//printf("Connexion en cours...\n");
	//fflush(stdout);

}

void disconnectFromServer(Server* server){
    close(server->socket);
}


