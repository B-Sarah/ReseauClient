#include "tile.h"


void displayTile(Tile tile){
    if(tile.character != NULL){
        displayCharacter(*tile.character);
    }
    if(tile.gameObject != NULL)
         displayObject(*tile.gameObject);
    else
        putchar(tile.skin);
}

int isPassable(Tile tile){
    if(tile.character != NULL) return 0;
    if(tile.skin == 'T') return 0;
    return 1;
}

