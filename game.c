#include "game.h"

Game* game;

void mainGameLoop(){

	while(game->isRunning){

	}
}

void updateCharacter(Character* character){

}

void addCharacter(Character* character){

}

Character* retrieveCharacter(int characterId){
	Character* retrievedCharacter = NULL;
	int i;

	for(i = 0; i < MAX_CHARACTERS; i++){
		if(game->characters[i]->id == characterId){

		}
	}
}




int main(){
	//(1)
	//Connexion
	//Quit

	//-> Connexion tcp + requete de log + reponse log
	// on creet un client
	// on se connecte au serveur
	// on envoie une requete de log
	// on attend la réponse
	// quand reponse : si positive, on passe à (2)
	// sinon on retourne a (1)


	//(2)
	//Play
	//Deconnexion
	//Quit

	//-> Play
	// le client demande info au serveur
	// recup d'info par le client
	//nouveau game initialisé avec les infos de personnages du serveur
	// et des infos locales (fichier, ou codé en dur)

	//lancer le mainGameLoop avec game initialisé




}








/*
int main(int argc, char** argv){
	Server server;

	connectToServer(&server, argv[1]);

	return 0;
}*/
