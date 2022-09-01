#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"
#include "configuracoes.h"
#include "melodias/asa_branca.h"



int ASA_BRANCA[] = {

	// Asa branca - Luiz Gonzaga
	// Score available at https://musescore.com/user/190926/scores/181370

	NOTE_G4,8, NOTE_A4,8, NOTE_B4,4, NOTE_D5,4, NOTE_D5,4, NOTE_B4,4,
	NOTE_C5,4, NOTE_C5,2, NOTE_G4,8, NOTE_A4,8,
	NOTE_B4,4, NOTE_D5,4, NOTE_D5,4, NOTE_C5,4,

	NOTE_B4,2, REST,8, NOTE_G4,8, NOTE_G4,8, NOTE_A4,8,
	NOTE_B4,4, NOTE_D5,4, REST,8, NOTE_D5,8, NOTE_C5,8, NOTE_B4,8,
	NOTE_G4,4, NOTE_C5,4, REST,8, NOTE_C5,8, NOTE_B4,8, NOTE_A4,8,

	NOTE_A4,4, NOTE_B4,4, REST,8, NOTE_B4,8, NOTE_A4,8, NOTE_G4,8,
	NOTE_G4,2, REST,8, NOTE_G4,8, NOTE_G4,8, NOTE_A4,8,
	NOTE_B4,4, NOTE_D5,4, REST,8, NOTE_D5,8, NOTE_C5,8, NOTE_B4,8,

	NOTE_G4,4, NOTE_C5,4, REST,8, NOTE_C5,8, NOTE_B4,8, NOTE_A4,8,
	NOTE_A4,4, NOTE_B4,4, REST,8, NOTE_B4,8, NOTE_A4,8, NOTE_G4,8,
	NOTE_G4,4, NOTE_F5,8, NOTE_D5,8, NOTE_E5,8, NOTE_C5,8, NOTE_D5,8, NOTE_B4,8,

	NOTE_C5,8, NOTE_A4,8, NOTE_B4,8, NOTE_G4,8, NOTE_A4,8, NOTE_G4,8, NOTE_E4,8, NOTE_G4,8,
	NOTE_G4,4, NOTE_F5,8, NOTE_D5,8, NOTE_E5,8, NOTE_C5,8, NOTE_D5,8, NOTE_B4,8,
	NOTE_C5,8, NOTE_A4,8, NOTE_B4,8, NOTE_G4,8, NOTE_A4,8, NOTE_G4,8, NOTE_E4,8, NOTE_G4,8,
	NOTE_G4,-2, REST,4
	
};

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

int get_startstop(){
	return pio_get(START_PIO,PIO_INPUT,START_PIO_IDX_MASK);
}

int get_selecao(){
	return pio_get(SELECAO_PIO,PIO_INPUT,SELECAO_PIO_IDX_MASK);
}

void buzzer_test(int freq){
	
	int conversao_s_us = 1000000.0;
	float meio_periodo = 1.0/(2*freq);
	 
	set_buzzer();
	delay_us(conversao_s_us*meio_periodo);
	clear_buzzer();
	delay_us(conversao_s_us*meio_periodo);
}

void tone(int freq, int time){
	float conversao_s_ms = 1000.0;
	float periodo_ms = conversao_s_ms/(freq);
	int qtd_pulsos = time/periodo_ms;
	
	for(int i = 0; i<qtd_pulsos; i++){
		set_buzzer();
		delay_ms(periodo_ms/2.0);
		clear_buzzer();
		delay_ms(periodo_ms/2.0);
	}
	
}

/*----------------- MAIN -----------------*/
int main (void)
{
	board_init();
	sysclk_init();
	delay_init();
	
  // Init button
	io_init();
	
	int time = 120;
	int wholenote =  (60000*4)/time;
	int notes = sizeof(ASA_BRANCA) / sizeof(ASA_BRANCA) / 2;
	int divider = 0, noteDuration = 0;
	
  // Init OLED
  //gfx_mono_ssd1306_init();
  
  // Escreve na tela um circulo e um texto
  //gfx_mono_draw_filled_circle(20, 16, 16, GFX_PIXEL_SET, GFX_WHOLE);
  //gfx_mono_draw_string("mundo", 50,16, &sysfont);

  /* Insert application code here, after the board has been initialized. */
	while(1) {
			
		for (int freq=200; freq<5000; freq+=50){
			tone(freq, 200 + freq/2);
			delay_ms(200);
		}		 
	}
}
