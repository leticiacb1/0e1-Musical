
/*
 * configuracoes.h
 *
 * Created: 31/08/2022 17:27:36
 *  Author: Leticia
 */ 

/*---------------- DEFINES ----------------*/

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

// Buzzer
#define BUZZER_PIO		PIOC
#define BUZZER_PIO_ID	ID_PIOC
#define BUZZER_PIO_IDX	13
#define BUZZER_PIO_IDX_MASK	(1 << BUZZER_PIO_IDX)

// Led
#define LED_PIO		PIOC
#define LED_PIO_ID	ID_PIOC
#define LED_PIO_IDX	8
#define LED_PIO_IDX_MASK	(1 << LED_PIO_IDX)

// Botão de START
#define START_PIO		PIOD
#define START_PIO_ID	ID_PIOD
#define START_PIO_IDX	28
#define START_PIO_IDX_MASK	(1 << START_PIO_IDX)

// Botão SELECT
#define SELECAO_PIO		PIOC
#define SELECAO_PIO_ID	ID_PIOC
#define SELECAO_PIO_IDX	31
#define SELECAO_PIO_IDX_MASK (1 << SELECAO_PIO_IDX)


/*---------------- PROTÓTIPOS ----------------*/

void io_init();

// Pôem 1 no PINO do buzzer
void set_buzzer();

// Põem 0 no PINO do buzzer
void clear_buzzer();

// Pôem 1 no PINO do LED
void set_led();

// Põem 0 no PINO do LED
void clear_led();

// Retorna status do botão START (1/0)
int get_startstop();

// Retorna status do botão SELECAO (1/0)
int get_selecao();

//Funcao para testar o buzzer
void buzzer_test(int freq);

//Funcao para reproduzir a onda quadrada no pino
void tone(int freq, int time);

void cria_playlist(music *pplaylist);

//toca musica
//void play(int freq, int time , int melodia[]);


