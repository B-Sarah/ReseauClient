#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdio.h>
#include <rpc/xdr.h>

typedef struct{
	char pseudo[30];
	char skin;
	int hp;
	int x;
	int y;
	long id;
}Character;

#endif

