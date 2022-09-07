
/*
 * musicas.h
 *
 * Created: 04/09/2022 12:26:12
 *  Author: Leticia
 */ 

/*
#include "melodias/asa_branca.h"
#include "melodias/doom.h"
#include "melodias/game_of_thrones.h"
#include "melodias/harry_potter.h"
#include "melodias/mario.h"
#include "melodias/pacman.h"
#include "melodias/star_wars.h"
#include "melodias/the_god_father.h"
#include "melodias/zelda.h"


#ifndef MUSIC
#define MUSIC
struct Music {
	char name[50];
	int music_time;
	int *melody;
};
#endif

typedef struct Music music;

music* playlist[];

void cria_playlist(){
	
	music mario = {"MARIO WORLD", TIME_MARIO, &mario_melody};
	music asa_branca = {"ASA BRANCA", TIME_ASABRANCA, &asa_branca_melody};
	
	*playlist = {&mario, &asa_branca};
}



/*																																																																																																																																																																																																																																																																																																																																													
music doom;
doom.name = "DOOM";
doom.music_time = TIME_DOOM;
doom.melody =  doom_melody;

music game_of_thrones;
game_of_thrones.name = "GAME OF THRONES";
game_of_thrones.music_time = TIME_GAMEOFTHRONES;
game_of_thrones.melody =  game_of_thrones_melody;

music harry_potter;
harry_potter.name = "HARRY POTTER";
harry_potter.music_time = TIME_HARRYPOTTER;
harry_potter.melody =  harry_potter_melody;




music pacman;
pacman.name = "PACMAN";
pacman.music_time = TIME_PACMAN;
pacman.melody =  pacman_melody;


music starwars;
starwars.name = "START WARS";
starwars.music_time = TIME_STARWARS;
starwars.melody =  star_wars_melody;

music the_god_father;
the_god_father.name = "THE GOD FATHER";
the_god_father.music_time = TIME_THEGODFATHER;
the_god_father.melody =  the_god_father_melody;

music zelda;
zelda.name = "ZELDA THEME";
zelda.music_time = TIME_ZELDA;
zelda.melody =  zelda_melody;


music playlist[] = {asa_branca}; //doom, game_of_thrones, harry_potter, mario, pacman , starwars, the_god_father, zelda };
*/ 
	