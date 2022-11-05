
/*
 * musicas.h
 *
 * Created: 10/09/2022 14:10:51
 *  Author: Leticia
 */ 

/*-------------------------------------------*/
/*------------------ DEFINES ----------------*/
/*-------------------------------------------*/
#ifndef MUSICA_H
#define MUSICA_H
// Buzzer
#define BUZZER_PIO		PIOC
#define BUZZER_PIO_ID	ID_PIOC
#define BUZZER_PIO_IDX	13
#define BUZZER_PIO_IDX_MASK	(1 << BUZZER_PIO_IDX)

// Struct das músicas
#ifndef MUSIC
#define MUSIC
struct Music {
	char name[50];
	int music_time;
	int *melody;
	int size;
};
#endif

typedef struct Music music;

/*-------------------------------------------*/
/* -------------- PROTÓTIPOS ----------------*/ 
/*-------------------------------------------*/

// Pôem 1 no PINO do buzzer
void set_buzzer();

// Põem 0 no PINO do buzzer
void clear_buzzer();

//Funcao para testar o buzzer
void buzzer_test(int freq);

//Funcao para reproduzir a onda quadrada no pino
void tone(int freq, int time);

//Funcao para preencher playlist com musicas
void fill_playlist(music* playlist);

//Funcao para tocar musica
void play(music song);
#endif