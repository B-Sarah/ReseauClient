#include "object.h"

/* xdr_object */

bool_t xdr_object(XDR* pt_xdr, Object* object){
	char skin = object->skin;
	char* pSkin = &skin;
	int* x = &(object->x);
	int* y = &(object->y);


	return(xdr_string(pt_xdr, pSkin, 30) &&
                xdr_int(pt_xdr, x) &&
                xdr_int(pt_xdr, x));

}
