#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <rpc/xdr.h>

typedef struct{
	char name[30];
	char password[20];
}Player;

#endif
