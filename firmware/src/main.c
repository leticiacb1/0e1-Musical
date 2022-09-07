#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"
#include "configuracoes.h"
#include "musicas.h"

/*---------------- GLOBAIS ----------------*/

volatile int IDX_PLAYLIST = 0;

/*---------------- FUNCOES ----------------*/

void io_init(){
	
	// -- Desativa WatchDog Timer --
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	// -- Inicializa PIO --
	pmc_enable_periph_clk(BUZZER_PIO_ID);
	pmc_enable_periph_clk(START_PIO_ID);
	pmc_enable_periph_clk(SELECAO_PIO_ID);
	
	// -- Configurando PINOS --
	pio_set_output(BUZZER_PIO, BUZZER_PIO_IDX_MASK, 1, 0, 0);
	
	// Inputs
	pio_configure(START_PIO, PIO_INPUT, START_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(START_PIO, START_PIO_IDX_MASK, 60);
	pio_configure(SELECAO_PIO, PIO_INPUT, SELECAO_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(SELECAO_PIO, SELECAO_PIO_IDX_MASK, 60);
}

void set_buzzer(){
	pio_set(BUZZER_PIO, BUZZER_PIO_IDX_MASK);
}

void clear_buzzer(){
	pio_clear(BUZZER_PIO, BUZZER_PIO_IDX_MASK);
}

void set_led(){
	pio_set(LED_PIO, LED_PIO_IDX_MASK);
}

void clear_led(){
	pio_clear(LED_PIO, LED_PIO_IDX_MASK);
}


int get_startstop(){
	return pio_get(START_PIO,PIO_INPUT,START_PIO_IDX_MASK);
}

int get_selecao(){
	return pio_get(SELECAO_PIO,PIO_INPUT,SELECAO_PIO_IDX_MASK);
}


// Função teste
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
	
	for(int i = 0; i<qtd_pulsos; i++){
		set_buzzer();
		delay_us(periodo_ms*500);           // (delay_ms *10^(3))/2 = delau_us
		clear_buzzer();
		delay_us(periodo_ms*500);
	}

}

/*---------------- MAIN ----------------*/

int main (void)
{
	
	board_init();
	sysclk_init();
	
	delay_init();
	
	// Init button
	io_init();
	
	// Preenchendo playlist de música
	music playlist[9];
	fill_playlist(playlist);
  
	/* Insert application code here, after the board has been initialized. */
	while(1) {
		
		// Musica selecionada
		music song = playlist[IDX_PLAYLIST];
		int *melody = (song.melody);
		
		// Variáveis
		int wholenote = (60000 * 4) / song.music_time;
		int divider = 0, noteDuration = 0;
		int notes = song.size / sizeof((*melody)) / 2;
		
		
		for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
			
			divider = melody[thisNote + 1];
			noteDuration = (wholenote) / abs(divider);
			
			if (divider < 0) {
				noteDuration *= 1.5;                                      // increases the duration in half for dotted notes
			}
			
			// we only play the note for 90% of the duration, leaving 10% as a pause
			tone(melody[thisNote], noteDuration * 0.9 );

			// Wait for the specief duration before playing the next note.
			delay_ms(noteDuration*0.1);

			// stop the waveform generation before the next note.
			clear_buzzer();

		}
	}
}