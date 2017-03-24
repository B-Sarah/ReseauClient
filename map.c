#include "map.h"


void displayMap(Map map){
    int i, j;
    system("clear");
    for(i = 0; i < MAP_WIDTH; i++){
        for(j = 0; j <MAP_HEIGHT; j++){
            displayTile(map.tiles[i][j]);
        }
        printf("\n");
    }


}


void initMap(const char* filePath, Map* map){
    FILE* file;
    int i = 0;
    int j = 0;
    char c;

    if((file =fopen(filePath,"r")) == NULL) printf("Error while initializing map from config file!\n");
        while ((c = getc(file)) != EOF){
            if(c != '\n'){
                map->tiles[i][j].x = i;
                map->tiles[i][j].y = j;
                map->tiles[i][j].skin = c;
            }

            j++;
            if(c == '\n'){
                j = 0;
                i++;
            }
        }
        fclose(file);
}

Tile* tileAt(Map* map, int x, int y){
    if(x < 0||x>=MAP_WIDTH||y<0||y>MAP_HEIGHT) return NULL;
    return &map->tiles[x][y];
}

void placeCharacter(Character* character, Map* map){

    tileAt(map, character->x, character->y)->character = character;
}

void moveCharacterTo(Character *character, Map* map, int x, int y){
    if(character == NULL) return;
    Tile* prevTile = tileAt(map, character->x, character->y);
    Tile* newTile = tileAt(map, x, y);

    if(newTile != NULL && isPassable(*newTile)){
        if(prevTile != NULL) prevTile->character = 0;
        character->x = x;
        character->y = y;
        newTile->character = character;
    }

}


void moveCharacter(Character *character, Map* map, Direction direction){
    if(character == NULL) return;
    Tile* prevTile = NULL;
    Tile* newTile = NULL;

    prevTile = tileAt(map, character->x, character->y);
    if(prevTile != NULL){
        switch(direction){
        case UP:
            newTile = tileAt(map, character->x - 1, character->y);
            if(newTile != NULL && isPassable(*newTile)) character->x -= 1;
            break;
        case DOWN:
            newTile = tileAt(map, character->x + 1, character->y);
            if(newTile != NULL && isPassable(*newTile)) character->x += 1;
            break;
        case RIGHT:
            newTile = tileAt(map, character->x, character->y + 1);
            if(newTile != NULL && isPassable(*newTile)) character->y += 1;
            break;
        case LEFT:
            newTile = tileAt(map, character->x, character->y - 1);
            if(newTile != NULL && isPassable(*newTile)) character->y -= 1;
            break;
        }
    }
    if(newTile != NULL){
        if(isPassable(*newTile)){
            prevTile->character = 0;
            newTile->character = character;
        }
    }

}

