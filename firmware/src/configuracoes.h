
/*
 * configuracoes.h
 *
 * Created: 31/08/2022 17:27:36
 *  Author: Leticia
 */ 

/*---------------- DEFINES ----------------*/

// Buzzer
#define BUZZER_PIO		PIOC
#define BUZZER_PIO_ID	ID_PIOC
#define BUZZER_PIO_IDX	13
#define BUZZER_PIO_IDX_MASK	(1 << BUZZER_PIO_IDX)

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

// Pôem 1 no PINO do buzzer
void set_buzzer();

// Põem 0 no PINO do buzzer
void clear_buzzer();

// Retorna status do botão START (1/0)
int get_startstop();

// Retorna status do botão SELECAO (1/0)
int get_selecao();

//Funcao para testar o buzzer
void buzzer_test(int freq);

//Funcao para reproduzir a onda quadrada no pino
void tone(int freq, int time);

//toca musica
void play(int freq, int time , int melodia[]);

