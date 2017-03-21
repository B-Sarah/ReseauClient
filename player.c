#include "player.h"

/* xdr_Player */

bool_t xdr_player(XDR* pt_xdr, Player* player){
	char* pName = player->name;
	char* pPwd = player->password;
	char** ppName = &pName;
	char** ppPwd = &pPwd;
	int* logged = &(player->logged);
	int* newAccount = &(player->newAccount);
	long* character_id = &player->character_id;

	printf("%d\n", logged);
	printf("%d\n", newAccount);

	return(xdr_string(pt_xdr, ppName, 30) &&
                xdr_string(pt_xdr, ppPwd, 20) &&
                xdr_long(pt_xdr, character_id) &&
                xdr_int(pt_xdr, logged) &&
                xdr_int(pt_xdr, newAccount));

}
