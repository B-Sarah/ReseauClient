#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <rpc/xdr.h>

#include "tile.h"
#define MAP_WIDTH 10
#define MAP_HEIGHT 10

typedef struct{
	Tile tiles[MAP_WIDTH][MAP_HEIGHT];
	int width;
	int height;
}Map;

#endif
