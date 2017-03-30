#include "character.h"

/* xdr_Character */

bool_t xdr_character(XDR* pt_xdr, Character* character){
	char* pPseudo = character->pseudo;
	char** ppPseudo = &pPseudo;
	char* skin = character->skin;
	char** pSkin = &skin;
	int* hp = &(character->hp);
	int* x = &(character->x);
	int* y = &(character->y);
	long* id = &(character->id);

	return(xdr_string(pt_xdr, ppPseudo, 30) &&
			xdr_string(pt_xdr, pSkin, 2) &&
			xdr_int(pt_xdr, hp) &&
			xdr_int(pt_xdr, x) &&
			xdr_int(pt_xdr, y) &&
           		xdr_long(pt_xdr, id));

}

void displayCharacter(Character character){
    putchar(character.skin[0]);
}
