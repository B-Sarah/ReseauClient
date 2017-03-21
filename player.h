#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <rpc/xdr.h>

typedef struct{
	char name[30];
	char password[20];
	long character_id;
	int logged;
	int newAccount;
}Player;

bool_t xdr_player(XDR* pt_xdr, Player* player);
#endif
