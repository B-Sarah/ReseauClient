#include "character.h"

/* xdr_Character */

bool_t xdr_Charcter(XDR* pt_xdr, Character* character){
	char* pPseudo = character->pseudo;
	char** ppPseudo = &pPseudo;
	char skin = character->skin;
	char* pSkin = &skin;
	int* hp = &(character->hp);
	int* x = &(character->x);
	int* y = &(character->y);
	int* id = &(character->id);

	return(xdr_string(pt_xdr, ppPseudo, 30) &&
			xdr_char(pt_xdr, pSkin) &&
			xdr_int(pt_xdr, hp) &&
			xdr_int(pt_xdr, x) &&
			xdr_int(pt_xdr, y) &&
            xdr_int(pt_xdr, id));

}
