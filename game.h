#ifndef GAME_H
#define GAME_H

#include "string.h"

#include "character.h"
#include "tile.h"
#include "map.h"
#include "player.h"
#include "object.h"
#include "client.h"

#define MAX_CHARACTERS 100
#define MAX_OBJECTS 40

#define MAIN_MENU 0
#define LOGIN_MENU 1
#define ACCOUNT_MENU 2
#define PLAY_MENU 3
#define QUIT_MENU 4

extern char* serverAddress;
int menuState;

typedef struct{
	Map map;
	Character* characters[MAX_CHARACTERS];
	Object* objects[MAX_OBJECTS];
	Player* player;
	int isRunning;
}Game;

extern Game game;

void mainGameLoop();

Character* retrieveCharacter(int characterId);
Object* retrieveObject(int objectId);


void updatePlayer(Player* player);
void updateCharacter(Character* character);
void updateObject(Object* object);

void createPlayerAccount();
void createPlayerAccount();

void userChoiceToAction(Server* server, int choice);

void menuHandler(Server* server);

void mainMenu();
void loginMenu(Server* server);
void accountMenu();
void playMenu();
int quitMenu(Server* server);

#endif
