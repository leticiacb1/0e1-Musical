#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

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
#define START_PIO_IDX_MASK	(1 << BUT1_IDX)

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

void get_startstop(){
	return pio_get(START_PIO,PIO_INPUT,START_PIO_IDX_MASK);
}

int get_selecao(){
	return pio_get(SELECAO_PIO,PIO_INPUT,SELECAO_PIO_IDX_MASK);
}

/*----------------- MAIN -----------------*/
int main (void)
{
	board_init();
	sysclk_init();
	delay_init();
	
  // Init button
	io_init();
	
  // Init OLED
	gfx_mono_ssd1306_init();
  
  // Escreve na tela um circulo e um texto
	gfx_mono_draw_filled_circle(20, 16, 16, GFX_PIXEL_SET, GFX_WHOLE);
  gfx_mono_draw_string("mundo", 50,16, &sysfont);

  /* Insert application code here, after the board has been initialized. */
	while(1) {

	}
}
