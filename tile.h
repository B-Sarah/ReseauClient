#ifndef TILE_H
#define TILE_H

#include <stdio.h>
#include <rpc/xdr.h>

#include "character.h"
#include "object.h"

typedef struct {
	int isObject;
	Object* gameObject;
	Character* character;
	int x;
	int y;

}Tile;

#endif
