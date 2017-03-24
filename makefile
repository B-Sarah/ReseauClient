.PHONY : all clean

jeu : client.o character.o game.o object.o player.o tile.o map.o 
	gcc -o jeu client.o character.o game.o object.o player.o tile.o map.o -lpthread
client.o : client.c client.h server.h
character.o: character.c character.h
game.o: game.c game.h
object.o: object.c object.h
player.o: player.c player.h
tile.o: tile.c tile.h
map.o: map.c map.h

clean: 
	@rm *.o
