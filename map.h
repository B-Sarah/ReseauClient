#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <rpc/xdr.h>

#include "tile.h"
#define MAP_WIDTH 10
#define MAP_HEIGHT 20

typedef enum{
    UP, DOWN, LEFT, RIGHT
}Direction;

typedef struct{
	Tile tiles[MAP_WIDTH][MAP_HEIGHT];
	int width;
	int height;
}Map;

void displayMap(Map map);
void initMap(const char* filePath, Map* map);
Tile* tileAt(Map* map, int x, int y);
void moveCharacterTo(Character *character, Map* map,int x, int y);
int moveCharacter(Character *character, Map* map, Direction direction);
void placeCharacter(Character* character, Map* map);

#endif

