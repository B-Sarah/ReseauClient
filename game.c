#include "game.h"

Game game;
char* serverAddress;

void mainGameLoop(){
    initMap("map1", &game.map);
    char input[10] = {0};

    /*Character character;
    character.skin = '@';
    character.id = 27;

    game.player->character_id = 27;
    game.characters[0] = &character;

    moveCharacterTo(&character, &game.map, 2,2);
*/
    game.isRunning = 1;

	while(game.isRunning){
       displayMap(game.map);
        readInput(input);
        handleInput(input);
	}
}

void readInput(char* input){
    scanf("%9s", input);
}

void handleInput(char* inputString){

    int isFighting = 0;

    if(strcmp(inputString, "z") == 0){
        isFighting = moveCharacter(retrieveCharacter(game.player->character_id),
                      &game.map, UP);
        encodeCharacter(retrieveCharacter(game.player->character_id));
    }
    else if(strcmp(inputString, "s") == 0){
        isFighting = moveCharacter(retrieveCharacter(game.player->character_id),
                      &game.map, DOWN);
        encodeCharacter(retrieveCharacter(game.player->character_id));
    }
    else if(strcmp(inputString, "q") == 0){
        isFighting = moveCharacter(retrieveCharacter(game.player->character_id),
                      &game.map, LEFT);
        encodeCharacter(retrieveCharacter(game.player->character_id));
    }
    else if(strcmp(inputString, "d") == 0){
        isFighting = moveCharacter(retrieveCharacter(game.player->character_id),
                      &game.map, RIGHT);
        encodeCharacter(retrieveCharacter(game.player->character_id));
    }
    else if(strcmp(inputString, "/quit") == 0){
        game.isRunning = 0;
    }

    /*if(isFighting){
        fight(tileAt(&game.map, game.characters[0]->x, game.characters[0]->y)->character);
    }*/

}

void fight(Character* charToFight){
    int result = rand() % 2;
    if(result == 1){
        charToFight->hp = 0;
    } else {
        game.characters[0]->hp = 0;
    }

    encodeCharacter(charToFight);
    encodeCharacter(game.characters[0]);
}

void addCharacter(Character* character){

}

Character* retrieveCharacter(int characterId){
	int i;

	for(i = 0; i < MAX_CHARACTERS; i++){
		if(game.characters[i] != NULL && game.characters[i]->id == characterId){
            return game.characters[i];

		}

	}
	return NULL;
}

int findCharacterSlot(){
    int i;

	for(i = 0; i < MAX_CHARACTERS; i++){
		if(game.characters[i] == NULL) return i;

	}
	return -1;
}

int findSlotOfCharacter(Character* c){
    int i;

	for(i = 0; i < MAX_CHARACTERS; i++){
		if(game.characters[i] == c) return i;

	}
	return 0;
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
    //printf("received update player\n");
    game.player->logged = player->logged;
    game.player->newAccount = player->newAccount;
    game.player->character_id = player->character_id;
    informUser();

    //TODO gerer new account echec
}

void updateCharacter(Character* character){
	int slot = 0;

    Character* updateCharacter = retrieveCharacter(character->id);
    if(updateCharacter == NULL){
        slot = findCharacterSlot();
        updateCharacter = (Character*)malloc(sizeof(Character));
        if(slot != -1){
            game.characters[slot] = updateCharacter;
        }
    }
	slot = findSlotOfCharacter(updateCharacter);
    strcpy(updateCharacter->pseudo, character->pseudo);

    /*if(character->hp == 0){
        if(slot == 0){
            disconnectFromServer();
            menuState = MAIN_MENU;
            system("clear");
            printf("**** Vous venez de mourir, veuillez vous reconnecter... (appuyez sur n'importe quelle touche) ****");
            getchar();
            game.isRunning = 0;
        }
        else{
            tileAt(&game.map, game.characters[0]->x, game.characters[0]->y)->character = game.characters[0];
            free(game.characters[slot]);

        }
        return;
	}*/


	if(slot == 0)
	    updateCharacter->skin[0] = character->skin[0];
	else
		updateCharacter->skin[0] = 'E';

    if(character->id == game.player->character_id)
        updateCharacter->skin[0] = '@';

    updateCharacter->id = character->id;

    updateCharacter->hp = character->hp;

    //printf("retrieved id : %ld\n", updateCharacter->id);

    moveCharacterTo(updateCharacter, &game.map, character->x, character->y);

	if(game.map.width != 0){
	    displayMap(game.map);
	}
}

void updateObject(Object* object){
    Object* updateObject = retrieveObject(object->id);

    updateObject->x = object->x;
    updateObject->y = object->y;
}

void informUser(){


    if(game.player->newAccount){
        printf(game.player->logged ? "Creation du compte reussie !\n\n" : "Echec, le d'utilisateur existe deja !\n\n");
        game.player->logged = 0;
        game.player->newAccount = 0;
        //if(game.player->logged) menuState = PLAY_MENU; else{
        menuState = MAIN_MENU;
            disconnectFromServer();
        //}
    }
    else{
        printf(game.player->logged ? "Connexion reussie !\n\n" : "Connexion refusée, nom d'utilisateur ou mot de passe incorrect !\n\n");
        if(!game.player->logged){
            disconnectFromServer();
            menuState = MAIN_MENU;
        } else{
            menuState = PLAY_MENU;
        }
    }
}



int main(int argc, char** argv){
    time_t t;
    srand((unsigned)time(&t));
    serverAddress = argv[1];

    game.isRunning = 0;
    Player p;
    p.newAccount = 0;
    p.logged = 0;
    game.player = &p;
	Server server;

    menuHandler(&server);


/* DEBUG
    Character character;
    strcpy(character.pseudo, "droweed");
    character.hp = 10;
    strcpy(character.skin, "@");
    character.id = 27;
    character.x = 0;
    character.y = 0;


  if(connectToServer(serverAddress) == 0){
        encodeCharacter(&character);
    }


*/
}

void menuHandler(Server* server){
    menuState = MAIN_MENU;

    while(TRUE){
        system("clear");
        switch(menuState){
        case MAIN_MENU:
            mainMenu();
            break;
        case LOGIN_MENU:
            loginMenu(server);
            break;
        case ACCOUNT_MENU:
            accountMenu();
            break;
        case PLAY_MENU:
            playMenu();
            break;
        case QUIT_MENU:
            if(quitMenu(server)) return;
            break;
	case WAITING_MENU:
		break;
        }
    }

}

void mainMenu(){
    int choice;

    printf("Bienvenue sur Old legion ! \n\n");
    printf("**************************\n \t Menu\n**************************\n");
	printf("1-- Déjà membre? Se connecter\n2-- Nouveau compte\n3-- Quitter\n");

    scanf("%d",&choice);
    fflush(stdin);
    if(choice == 1) menuState = LOGIN_MENU;
    else if(choice == 2) menuState = ACCOUNT_MENU;
    else if(choice == 3) menuState = QUIT_MENU;
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
    printf("\n");

    strcpy(game.player->name, name);
    strcpy(game.player->password, password);

    game.player->logged = 0;
    game.player->newAccount = 0;
    game.player->character_id = 0;
    if(connectToServer(serverAddress) == 0){
        encodePlayer(game.player);
    }
    else{
        menuState = MAIN_MENU;
        return;
    }
    //if()
    //printf("update %d\n ", game.player->newAccount);


    menuState = WAITING_MENU;
}

void accountMenu(){
    char name[30] = {0};
    char password[20] = {0};
    int lenName=0, lenPwd = 0;

    printf("\tNouveau compte\n\n");

    do{
        printf("Saisissez votre nom (30 caracteres au max)... ");
        scanf("%s",name);
        printf("Saisissez votre mot de passe (moins de 20 caracteres)... ");
        scanf("%s",password);
        lenName = strlen(name);
        lenPwd = strlen(password);
    } while (lenName >= 30 || lenPwd >= 20);

    printf("\n");
    game.player->newAccount = 1;
    game.player->logged = 0;
    game.player->character_id = 0;
    strcpy(game.player->name, name);
    strcpy(game.player->password, password);

    if(connectToServer(serverAddress) == 0){
        encodePlayer(game.player);
        menuState = WAITING_MENU;
        return;
    }
    menuState = MAIN_MENU;



}
void playMenu(){
    int choice;
    printf("\tGame\n\n");
    printf("1-- Jouer\n2-- Se deconnecter\n3-- Quitter\n");

    scanf("%d",&choice);
    fflush(stdin);
    if(choice == 1){
        mainGameLoop();
        disconnectFromServer();
        menuState = MAIN_MENU;
    }
    else if(choice == 2){
        disconnectFromServer();
        menuState = MAIN_MENU;
    }
    else if(choice == 3) menuState = QUIT_MENU;
}


int quitMenu(){
    char response = ' ';
    int count = 0;
    printf("Voulez vraiment quitter ? (oui=o ou non=n)\n");


    do{
        if(count == 5){
            printf("Vous avez dépasser le nombre de tentatives maximum, retour au menu ... \n");
            return 0;
        }
        scanf("%c",&response);
        fflush(stdin);
        count++;
        if(response != 'o' && response != 'n' && response != '\n'){
            printf("Votre choix est invalide! réssayez (oui=o ou non=n)!");
        }
    }while(response != 'o' && response != 'n');

    if(response == 'o'){
        printf("Bye bye .. !\n");
        disconnectFromServer();
        return 1;

    }
    else if(response == 'n'){
        return 0;
    }
    return 0;
}


void hasBeenDeconected(){
    printf("Vous avez été déconnectée du serveur... Press 0 to continue.\n\n");
    disconnectFromServer();
    menuState = MAIN_MENU;
 }











