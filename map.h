#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <rpc/xdr.h>

#include "tile.h"

typedef struct{
	Tile tiles[10][10];
	int width;
	int height;
}Map;

#endif
