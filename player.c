#include "player.h"

/* xdr_Player */

bool_t xdr_player(XDR* pt_xdr, Player* player){
	char* pName = player->name;
	char* pPwd = player->password;
	char** ppName = &pName;
	char** ppPwd = &pPwd;

	return(xdr_string(pt_xdr, ppName, 30) &&
			xdr_string(pt_xdr, ppPwd, 20));

}
