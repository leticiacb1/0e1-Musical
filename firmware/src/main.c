#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"
#include "configuracoes.h"
#include "musicas.h"

/*---------------- GLOBAIS ----------------*/

volatile int SELECT_IDX_PLAYLIST = 0;
volatile int init_state = 0;

/* flag */

// Inicializa tocando música (1) e SELECT não pressionado
volatile char but_START_PAUSE_flag = 1; 
volatile char but_SELECT_flag = 0; 


/*---------------- CALLBACKS ----------------*/

void but_start_pause_callback(void)
{
	if( but_START_PAUSE_flag == 1 ){
		
		// Caso esteja em "play" pausar
		but_START_PAUSE_flag = 0;
	}else{
		
		// Caso esteja em "pause" dar play
		but_START_PAUSE_flag = 1;
	}
}

void but_select_callback(void){
	
	but_SELECT_flag = 1;
		
	if(SELECT_IDX_PLAYLIST >= 8){
		SELECT_IDX_PLAYLIST=0;
	}else{
		SELECT_IDX_PLAYLIST+=1;
	}
		
}


/*---------------- FUNCOES ----------------*/

void io_init(){
	
	// ----- Desativa WatchDog Timer -----
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	// ----- Inicializa PIO -----
	pmc_enable_periph_clk(BUZZER_PIO_ID);
	pmc_enable_periph_clk(START_PIO_ID);
	pmc_enable_periph_clk(SELECT_PIO_ID);
	
	// ----- Configurando PINOS -----
	pio_set_output(BUZZER_PIO, BUZZER_PIO_IDX_MASK, 1, 0, 0);
	
	//  ----- Inputs -----
	pio_configure(START_PIO, PIO_INPUT, START_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(START_PIO, START_PIO_IDX_MASK, 60);
	pio_configure(SELECT_PIO, PIO_INPUT, SELECT_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(SELECT_PIO, SELECT_PIO_IDX_MASK, 60);
	
	// ----- Configurando interrupts ----- 
	
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
	
	// Configura NVIC para receber interrupcoes do PIO do botao com prioridade 4 
	NVIC_EnableIRQ(START_PIO_ID);
	NVIC_SetPriority(START_PIO_ID, 4); 
	
	NVIC_EnableIRQ(SELECT_PIO_ID);
	NVIC_SetPriority(SELECT_PIO_ID, 4); 
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
	return pio_get(SELECT_PIO,PIO_INPUT,SELECT_PIO_IDX_MASK);
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

void play(music song){
	
	// Array de melodias
	int *melody = (song.melody);
	
	// Variáveis
	int wholenote = (60000 * 4) / song.music_time;
	int divider = 0, noteDuration = 0;
	int notes = song.size / sizeof((*melody)) / 2;
	
	for(int thisNote = init_state; (thisNote < notes * 2) && but_START_PAUSE_flag && !but_SELECT_flag ; thisNote = thisNote + 2){
		
		divider = melody[thisNote + 1];
		noteDuration = (wholenote) / abs(divider);
		
		// increases the duration in half for dotted notes
		if (divider < 0) {
			noteDuration *= 1.5;
		}

		// we only play the note for 90% of the duration, leaving 10% as a pause
		tone(melody[thisNote], noteDuration * 0.9 );

		// Wait for the specief duration before playing the next note.
		delay_ms(noteDuration*0.1);

		// stop the waveform generation before the next note.
		clear_buzzer();
		
		// Setando variável de controle para play/pause.
		init_state = thisNote;
		
		// Reinicializando
		if(thisNote == (2*notes - 2)){
			init_state = 0;
		}
		
	}
	
}

void limpa_pause(){
	// Limpa lado esquerdo
	gfx_mono_generic_draw_vertical_line(10, 5, 12, GFX_PIXEL_CLR );
	gfx_mono_generic_draw_vertical_line(11, 5, 12, GFX_PIXEL_CLR );
	gfx_mono_generic_draw_vertical_line(12, 5, 12, GFX_PIXEL_CLR );
	
	// Limpa lado direito 
	gfx_mono_generic_draw_vertical_line(18, 5, 12, GFX_PIXEL_CLR );
	gfx_mono_generic_draw_vertical_line(19, 5, 12, GFX_PIXEL_CLR );
	gfx_mono_generic_draw_vertical_line(20, 5, 12, GFX_PIXEL_CLR );		
}

void limpa_play(){
	// Limpa o meio
	gfx_mono_generic_draw_vertical_line(14, 7, 8, GFX_PIXEL_CLR );
	gfx_mono_generic_draw_vertical_line(16, 8, 6, GFX_PIXEL_CLR );
}

// ------------ DA POBLEMA -------
void limpa_estado(){
	gfx_mono_draw_filled_rect(10,5, 12 , 12, GFX_PIXEL_CLR);
}

void desenha_botao_pause(){
	
	limpa_play();
	
	// Lado esquerdo 
	gfx_mono_generic_draw_vertical_line(10, 5, 12, GFX_PIXEL_SET );
	gfx_mono_generic_draw_vertical_line(11, 5, 12, GFX_PIXEL_SET );
	gfx_mono_generic_draw_vertical_line(12, 5, 12, GFX_PIXEL_SET );

	// Lado direito 
	gfx_mono_generic_draw_vertical_line(18, 5, 12, GFX_PIXEL_SET );
	gfx_mono_generic_draw_vertical_line(19, 5, 12, GFX_PIXEL_SET );
	gfx_mono_generic_draw_vertical_line(20, 5, 12, GFX_PIXEL_SET );
}

void desenha_botao_play(){
	
	limpa_pause();
		
	gfx_mono_generic_draw_vertical_line(10, 5, 12, GFX_PIXEL_SET );
	gfx_mono_generic_draw_vertical_line(12, 6, 10, GFX_PIXEL_SET );
	gfx_mono_generic_draw_vertical_line(14, 7, 8, GFX_PIXEL_SET );
	gfx_mono_generic_draw_vertical_line(16, 8, 6, GFX_PIXEL_SET );
	gfx_mono_generic_draw_vertical_line(18, 9, 4, GFX_PIXEL_SET );
	gfx_mono_generic_draw_vertical_line(20, 10, 2, GFX_PIXEL_SET );
	
	//  Atualiza barra de progresso.
	//gfx_mono_draw_filled_rect(14,22, i*qtd_cresce , 6,GFX_PIXEL_SET);
	
	// sprintf(str_delay, "%4d ms", delay);
	// gfx_mono_draw_string(str_delay, 65, 8, &sysfont);
}

void desenha_nome_musica(char * nome){
	
	char str_music_idx[128];
		
	sprintf(str_music_idx, "%d: ", SELECT_IDX_PLAYLIST);
	gfx_mono_draw_string(str_music_idx, 36, 8, &sysfont);
	gfx_mono_draw_string(nome, 48 , 8, &sysfont);
}

/*---------------- MAIN ----------------*/

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
	
	/* Insert application code here, after the board has been initialized. */
	while(1) {
		
		// Musica selecionada
		music song = playlist[SELECT_IDX_PLAYLIST];
		desenha_nome_musica(song.name);
		
		if(but_START_PAUSE_flag && !but_SELECT_flag){
			desenha_botao_play();
			play(song);
		}
		
		if(!but_START_PAUSE_flag){
			desenha_botao_pause();
		}
		
		
		if(but_SELECT_flag){
			init_state = 0;
			but_SELECT_flag = 0;
		}
		
		
		
	}
}