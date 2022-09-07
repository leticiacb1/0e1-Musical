
/*
 * musicas.h
 *
 * Created: 04/09/2022 12:26:12
 *  Author: Leticia
 */ 


#include "configuracoes.h"
#include "melodias/asa_branca.h"
#include "melodias/doom.h"
#include "melodias/game_of_thrones.h"
#include "melodias/harry_potter.h"
#include "melodias/mario.h"
#include "melodias/pacman.h"
#include "melodias/star_wars.h"
#include "melodias/the_god_father.h"
#include "melodias/zelda.h"


void fill_playlist(music* playlist){
	
	//Definindo structs de musicas
	music asa_branca = {"ASA BRANCA", TIME_ASABRANCA, &asa_branca_melody, SIZE_ASA};
	music doom = {"DOOM", TIME_DOOM, &doom_melody, SIZE_DOOM};
	music game_of_thrones = {"GAME OF THRONES", TIME_GAMEOFTHRONES, &game_of_thrones_melody , SIZE_GAMEOFTHRONES};
	music harry_potter = {"HARRY POTTER", TIME_HARRYPOTTER, &harry_potter_melody , SIZE_HARRYPOTTER};
	music mario = {"MARIO WORLD", TIME_MARIO, &mario_melody , SIZE_MARIO};
	music pacman = {"PACMAN", TIME_PACMAN, &pacman_melody , SIZE_PACMAN};
	music star_wars = {"STAR WARS", TIME_STARWARS, &star_wars_melody , SIZE_STARWARS};
	music the_god_father = {"GOD FATHER", TIME_THEGODFATHER, &the_god_father_melody, SIZE_THEGODFATHER};
	music zelda = {"ZELDA", TIME_ZELDA, &zelda_melody , SIZE_ZELDA};
	
	// Preenchendo playlist
	playlist[0] = asa_branca;
	playlist[1] = doom;
	playlist[2] = game_of_thrones;
	playlist[3] = harry_potter;
	playlist[4] = mario;
	playlist[5] = pacman;
	playlist[6] = star_wars;
	playlist[7] = the_god_father;
	playlist[8] = zelda;
}
