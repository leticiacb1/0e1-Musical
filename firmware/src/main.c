/*-------------------------------------------*/
/*------------------ INCLUDES ---------------*/
/*-------------------------------------------*/

#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

#include "configuracoes.h"
#include "musica.h"
#include "leds.h"
#include "display.h"


/*-------------------------------------------*/
/*------------------ GLOBAIS ----------------*/
/*-------------------------------------------*/


volatile int SELECT_IDX_PLAYLIST = 0;
volatile int init_state = 0;


/* flag */

// Inicializa música funcionando (1) e SELECT não pressionado
volatile char but_START_PAUSE_flag = 1; 
volatile char but_SELECT_flag = 0; 
volatile char init_screen = 1;


/*-------------------------------------------*/
/*---------------- CALLBACKS ----------------*/
/*-------------------------------------------*/


void but_init(void){
	if(get_init() == 0 && init_screen == 1){
		init_screen = 0;
	}
}

void but_start_pause_callback(void)
{
	but_START_PAUSE_flag = !but_START_PAUSE_flag;
}

void but_select_callback(void){
	
	but_SELECT_flag = 1;
		
	if(SELECT_IDX_PLAYLIST >= 8){
		SELECT_IDX_PLAYLIST=0;
	}else{
		SELECT_IDX_PLAYLIST+=1;
	}
		
}

/*-------------------------------------------*/
/*----------------- FUNCOES -----------------*/
/*-------------------------------------------*/


int get_startstop(){
	return pio_get(START_PIO,PIO_INPUT,START_PIO_IDX_MASK);
}

int get_selecao(){
	return pio_get(SELECT_PIO,PIO_INPUT,SELECT_PIO_IDX_MASK);
}

int get_init(){
	return pio_get(INIT_PIO,PIO_INPUT,INIT_PIO_IDX_MASK);
}

void io_init(){
	
	// ----- Desativa WatchDog Timer -----
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	// ----- Inicializa PIO -----
	pmc_enable_periph_clk(BUZZER_PIO_ID);
	pmc_enable_periph_clk(INIT_PIO_ID);
	pmc_enable_periph_clk(START_PIO_ID);
	pmc_enable_periph_clk(SELECT_PIO_ID);
	
	pmc_enable_periph_clk(LED1_PIO_ID);
	pmc_enable_periph_clk(LED2_PIO_ID);
	pmc_enable_periph_clk(LED3_PIO_ID);
	
	
	// ----- Configurando PINOS -----
	pio_set_output(BUZZER_PIO, BUZZER_PIO_IDX_MASK, 1, 0, 0);
	
	pio_set_output(LED1_PIO, LED1_PIO_IDX_MASK, 1, 0, 0);
	pio_set_output(LED2_PIO, LED2_PIO_IDX_MASK, 1, 0, 0);
	pio_set_output(LED3_PIO, LED3_PIO_IDX_MASK, 1, 0, 0);
	
	//  ----- Inputs -----
	pio_configure(INIT_PIO, PIO_INPUT, INIT_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(INIT_PIO, INIT_PIO_IDX_MASK, 60);
	pio_configure(START_PIO, PIO_INPUT, START_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(START_PIO, START_PIO_IDX_MASK, 60);
	pio_configure(SELECT_PIO, PIO_INPUT, SELECT_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(SELECT_PIO, SELECT_PIO_IDX_MASK, 60);
	
	// ----- Configurando interrupts ----- 
	
	pio_handler_set(INIT_PIO,
					INIT_PIO_ID,
					INIT_PIO_IDX_MASK,
					PIO_IT_FALL_EDGE,
					but_init);
	
	// Configurando função callback para botao START_PAUSE
	pio_handler_set(START_PIO,
					START_PIO_ID,
					START_PIO_IDX_MASK,
					PIO_IT_FALL_EDGE,
					but_start_pause_callback);
					
	// Configurando função callback para botao SELECT
	pio_handler_set(SELECT_PIO,
					SELECT_PIO_ID,
					SELECT_PIO_IDX_MASK,
					PIO_IT_FALL_EDGE,
					but_select_callback);
					
	// Ativa interrupção e limpa primeira IRQ gerada na ativacao
	pio_enable_interrupt(START_PIO, START_PIO_IDX_MASK);
	pio_get_interrupt_status(START_PIO);
	
	pio_enable_interrupt(SELECT_PIO, SELECT_PIO_IDX_MASK);
	pio_get_interrupt_status(SELECT_PIO);
	
	pio_enable_interrupt(INIT_PIO, INIT_PIO_IDX_MASK);
	pio_get_interrupt_status(INIT_PIO);
	
	// Configura NVIC para receber interrupcoes do PIO do botao com prioridade 4 
	NVIC_EnableIRQ(START_PIO_ID);
	NVIC_SetPriority(START_PIO_ID, 4); 
	
	NVIC_EnableIRQ(SELECT_PIO_ID);
	NVIC_SetPriority(SELECT_PIO_ID, 4); 
	
	NVIC_EnableIRQ(INIT_PIO_ID);
	NVIC_SetPriority(INIT_PIO_ID, 4); 
}

void play(music song){
	
	// Array de melodias
	int *melody = (song.melody);
	
	// Variáveis
	int wholenote = (60000 * 4) / song.music_time;
	int divider = 0, noteDuration = 0;
	int notes = song.size / sizeof((*melody)) / 2;
	
	//  Quão maior é o numero de notas em relação ao tamanho da barra
	int delta = 20;
	
	for(int thisNote = init_state; (thisNote < notes * 2) && but_START_PAUSE_flag && !but_SELECT_flag ; thisNote = thisNote + 2){
		
		divider = melody[thisNote + 1];
		noteDuration = (wholenote) / abs(divider);

		if (divider < 0) {
			noteDuration *= 1.5;
		}

		// Controle para desenhar barra progresso:
		
		if ((thisNote/2)%(notes/delta) == 0) {
			int multiplo = (thisNote/2)/(notes/delta);
			progresso(multiplo, delta);
		}
		
		tone(melody[thisNote], noteDuration * 0.9 );
		delay_ms(noteDuration*0.1);
		clear_buzzer();
		
		init_state = thisNote;
		
		// Reinicializando
		if(thisNote == (2*notes - 2)){
			init_state = 0;
			limpa_progresso();
		}
		
	}
	
}

void anima_init(){
	
	while(init_screen){
		
		for(int i = 0; i<=128 && init_screen;i+=8){
			delay_ms(100);
			desenha_traco(i+8,4,GFX_PIXEL_SET);
			delay_ms(50);
			desenha_traco(120-i,30,GFX_PIXEL_SET);
		}
		
		for(int i = 0; i<=128 && init_screen ;i+=8){
			delay_ms(100);
			desenha_traco(i+8,4,GFX_PIXEL_CLR);
			delay_ms(50);
			desenha_traco(120-i,30,GFX_PIXEL_CLR);
		}
		
		delay_ms(3000);
		
	}
	
}

void tela_inicio(){
	limpa_tudo();
	gfx_mono_draw_string("-- PLAY THE MUSIC --", 3, 16, &sysfont);
	anima_init();
	
}

/*-------------------------------------------*/
/*------------------ MAIN -------------------*/
/*-------------------------------------------*/

int main (void)
{
	
	board_init();
	sysclk_init();
	
	delay_init();
	
	// Init OLED
	gfx_mono_ssd1306_init();
	
	// Init button
	io_init();
	
	// Preenchendo playlist de música
	music playlist[9];
	fill_playlist(playlist);
	
	// Tela de inicio
	tela_inicio();
	
	int apena_1_vez = 1;
	if(apena_1_vez){
		limpa_tudo();
		apena_1_vez = 0;
	}
	
	/* Insert application code here, after the board has been initialized. */
	while(1) {
		
		// Musica selecionada
		music song = playlist[SELECT_IDX_PLAYLIST];
		
		if(!init_screen){
			
			if(but_START_PAUSE_flag && !but_SELECT_flag){
				desenha_nome_musica(song.name, SELECT_IDX_PLAYLIST);
				desenha_botao_play();
				play(song);
			}
			
			if(!but_START_PAUSE_flag){
				desenha_botao_pause();
			}
			
			
			if(but_SELECT_flag){
				desenha_nome_musica(song.name, SELECT_IDX_PLAYLIST);
				limpa_progresso();
				
				init_state = 0;
				but_SELECT_flag = 0;
			}
			
		}
			
	}
}