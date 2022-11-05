
/*
 * musica.c
 *
 * Created: 10/09/2022 13:40:53
 *  Author: Leticia
 */ 


/*-------------------------------------------*/
/*------------------ INCLUDES ---------------*/
/*-------------------------------------------*/

#include <asf.h>

#include "melodias/asa_branca.h"
#include "melodias/doom.h"
#include "melodias/game_of_thrones.h"
#include "melodias/harry_potter.h"
#include "melodias/mario.h"
#include "melodias/pacman.h"
#include "melodias/star_wars.h"
#include "melodias/the_god_father.h"
#include "melodias/zelda.h"

#include "configuracoes.h"
#include "musica.h"
#include "leds.h"


/*-------------------------------------------*/
/*------------------ FUNCOES ----------------*/
/*-------------------------------------------*/


void set_buzzer(){
	pio_set(BUZZER_PIO, BUZZER_PIO_IDX_MASK);
}

void clear_buzzer(){
	pio_clear(BUZZER_PIO, BUZZER_PIO_IDX_MASK);
}



void buzzer_test(int freq){
	
	int conversao_s_us = 1000000.0;
	float meio_periodo = 1.0/(2*freq);
	
	set_buzzer();
	delay_us(conversao_s_us*meio_periodo);
	clear_buzzer();
	delay_us(conversao_s_us*meio_periodo);
}


/**
* freq: Frequecia em Hz
* time: Tempo em ms que o tom deve ser gerado
*/
void tone(int freq, int time){
	float conversao_s_ms = 1000.0;
	float periodo_ms = conversao_s_ms/(freq);
	int qtd_pulsos = time/periodo_ms;
	
	if (freq == 0){
		delay_ms(time);
		return;
	}
	
	for(int i = 0; i<qtd_pulsos; i++){
		
		acende_leds(freq);
		set_buzzer();
		
		delay_us(periodo_ms*500);           // (delay_ms *10^(3))/2 = delau_us
		
		apaga_leds();
		clear_buzzer();
		
		delay_us(periodo_ms*500);
		
	}

}


void fill_playlist(music* playlist){
	
	//Definindo structs de musicas
	music asa_branca = {"ASA BRANCA", TIME_ASABRANCA, &asa_branca_melody, SIZE_ASA};
	music doom = {"DOOM", TIME_DOOM, &doom_melody, SIZE_DOOM};
	music game_of_thrones = {"GOT", TIME_GAMEOFTHRONES, &game_of_thrones_melody , SIZE_GAMEOFTHRONES};
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

