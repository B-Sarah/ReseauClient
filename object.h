#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <rpc/xdr.h>


typedef struct {
	char skin;
	int x;
 	int y;
 	long id;

}Object;

bool_t xdr_object(XDR* pt_xdr, Object* object);

void displayObject(Object object);

#endif



