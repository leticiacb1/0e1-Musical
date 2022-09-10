
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

// Progress Bar
#define PROGRESS_WIDTH	120
#define PROGRESS_HEIGHT 6 

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

// Botão de INICIO
#define INIT_PIO		PIOA
#define INIT_PIO_ID		ID_PIOA
#define INIT_PIO_IDX	19
#define INIT_PIO_IDX_MASK	(1 << INIT_PIO_IDX)

// Botão de START
#define START_PIO		PIOD
#define START_PIO_ID	ID_PIOD
#define START_PIO_IDX	28
#define START_PIO_IDX_MASK	(1 << START_PIO_IDX)

// Botão SELECT
#define SELECT_PIO		PIOC
#define SELECT_PIO_ID	ID_PIOC
#define SELECT_PIO_IDX	31
#define SELECT_PIO_IDX_MASK (1 << SELECT_PIO_IDX)


// Configurações doS LEDS
#define LED1_PIO            PIOA                  
#define LED1_PIO_ID         ID_PIOA                
#define LED1_PIO_IDX        0                     
#define LED1_PIO_IDX_MASK  (1 << LED1_PIO_IDX)    

#define LED2_PIO            PIOC
#define LED2_PIO_ID         ID_PIOC
#define LED2_PIO_IDX        30
#define LED2_PIO_IDX_MASK  (1 << LED2_PIO_IDX)

#define LED3_PIO            PIOB
#define LED3_PIO_ID         ID_PIOB
#define LED3_PIO_IDX        2
#define LED3_PIO_IDX_MASK  (1 << LED3_PIO_IDX)


/*---------------- PROTÓTIPOS ----------------*/

void io_init();

// Pôem 1 no PINO do buzzer
void set_buzzer();

// Põem 0 no PINO do buzzer
void clear_buzzer();

// Pôem 0 no PINO do LED
void set_led1();
void set_led2();
void set_led3();

// Põem 1 no PINO do LED
void clear_led1();
void clear_led2();
void clear_led3();

// Função acende leds 
void acende_leds(int freq);

// Função apaga leds
void apaga_leds();

// Retorna status do botão START (1/0)
int get_startstop();

// Retorna status do botão SELECAO (1/0)
int get_selecao();

// Botao de tela de inicio (But3)
int get_init();

//Funcao para testar o buzzer
void buzzer_test(int freq);

//Funcao para reproduzir a onda quadrada no pino
void tone(int freq, int time);

//Funcao para preencher playlist com musicas
void fill_playlist(music* playlist);

// Toca musica
void play(music song);


