#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdio.h>
#include <rpc/xdr.h>

const static char OUR_CHARACTER = '@';
const static char OTHER_CHARACTER = 'E';

typedef struct{
	char pseudo[30];
	char skin;
	int hp;
	int x;
	int y;
	long id;
}Character;

bool_t xdr_character(XDR* pt_xdr, Character* character);

void displayCharacter(Character character);

#endif


