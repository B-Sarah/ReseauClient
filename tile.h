#ifndef TILE_H
#define TILE_H

#include <stdio.h>
#include <rpc/xdr.h>

#include "character.h"
#include "object.h"

const static char GRASS = ',';
const static char TREE = 'T';

typedef struct {
	int isObject;
	Object* gameObject;
	Character* character;
	int x;
	int y;
	char skin;
	int passable;

}Tile;

void displayTile(Tile tile);
int isPassable(Tile tile);

#endif


