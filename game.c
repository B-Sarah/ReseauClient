#include "game.h"

Game game;
char* serverAddress;

void mainGameLoop(){

	while(game.isRunning){
        //handleInput();


        //refreshMap();
        usleep(50);


	}
}

void addCharacter(Character* character){

}

Character* retrieveCharacter(int characterId){
	int i;

	for(i = 0; i < MAX_CHARACTERS; i++){
		if(game.characters[i]->id == characterId){
            return game.characters[i];

		}

	}
	return NULL;
}

Object* retrieveObject(int objectId){
	int i;

	for(i = 0; i < MAX_OBJECTS; i++){
		if(game.objects[i]->id == objectId){
            return game.objects[i];

		}

	}
	return NULL;
}


void updatePlayer(Player* player){
    game.player->logged = player->logged;
}

void updateCharacter(Character* character){
    Character* updateCharacter = retrieveCharacter(character->id);

    updateCharacter->hp = character->hp;
    updateCharacter->x = character->x;
    updateCharacter->y = character->y;

}

void updateObject(Object* object){
    Object* updateObject = retrieveObject(object->id);

    updateObject->x = object->x;
    updateObject->y = object->y;

}





int main(int argc, char** argv){
    serverAddress = argv[1];
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

    game.isRunning = 1;
    Player p;
    game.player = &p;
	Server server;

    menuHandler(&server);
}

void menuHandler(Server* server){
    menuState = MAIN_MENU;
    int choice;

    while(TRUE){
        switch(menuState){
        case MAIN_MENU:
            mainMenu();

            scanf("%d",&choice);
            if(choice == 1) menuState = LOGIN_MENU;
            else if(choice == 2) menuState = ACCOUNT_MENU;
            else menuState = QUIT_MENU;
            break;
        case LOGIN_MENU:
            loginMenu(server);
            break;

        case QUIT_MENU:
            quitMenu(server);
            break;
        }
    }

}

void mainMenu(){
    printf("Bienvenue sur Old legion ! \n\n");
    printf("**************************\n \t Menu\n**************************\n");
	printf("1-- Déjà membre? Se connecter\n2-- Nouveau compte\n3-- Quitter\n");
}


void loginMenu(Server* server){
    int count = 0;
    char name[30];
    char password[20];
    printf("\tLogin\n\n");

	do{
        if(count == 3){
            printf("Vous avez dépasser le nombre de tentatives maximum, retour au menu principale... \n");
            menuState = MAIN_MENU;
            return;
        }
        printf("Saisissez votre nom ... ");
        scanf("%s",name);
        printf("Saisissez votre mot de passe ... ");
        scanf("%s",password);
    }while(strlen(name) >= 30 || strlen(password) >= 20);

    strcpy(game.player->name, name);
    strcpy(game.player->password, password);

    game.player->logged = 0;
    game.player->newAccount = 0;

    encodePlayer(server, game.player);

    menuState = PLAY_MENU;
}

void accountMenu(){
}
void playMenu(){
}

/*void createPlayerAccount(){
    Player* player = &(accountInformation());
    game->player = Player;

}*/

/*Player accountInformation(){
    char[30] name = {0};
    char[20] password = {0};

	do{
    scanf("Saisissez votre nom (30caractères au max) !\n%s",&name);
    scanf("Saisissez votre mot de passe (moins de 20 caactères) !\n%s",&password);
    }while(strlen(name) >= 30 || strlen(password) >= 20);

    Player player;
    player.newAccount = 1;
    player.logged = 0;
    strcpy(player.name, name);
    strcpy(player.password, password);

    return player;

}*/


int quitMenu(Server* server){
    char response = ' ';
    int count = 0;
    printf("Voulez vraiment quitter ? (oui=o ou non=n)\n");

    do{
        if(count == 5){
            printf("Vous avez dépasser le nombre de tentatives maximum, retour au menu principale... \n");
            menuState = MAIN_MENU;
        }
        response = getchar();
        count++;
        if(response != 'o' && response != 'n'){
            printf("Votre choix est invalide! réssayez (oui=o ou non=n)!");
        }
    }while(response != 'o' && response != 'n');

    if(response == 'o'){
        printf("Bye bye .. !");
        disconnectFromServer(server);
        return 1;

    }
    else if(response == 'n'){
        menuState = MAIN_MENU;
    }
    return 0;
}








