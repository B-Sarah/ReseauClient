#ifndef GAME_H 
#define GAME_H



#include "character.h"
#include "tile.h"
#include "map.h"
#include "player.h"
#include "object.h"
#include "client.h"

#define MAX_CHARACTERS 100
#define MAX_OBJECTS 40

typedef struct{
	Map map;
	Character* characters[MAX_CHARACTERS];
	Object* objects[MAX_OBJECTS];
	int isRunning;
}Game;

extern Game* game;

void mainGameLoop();


#endif
