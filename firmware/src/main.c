#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"
#include "configuracoes.h"
#include "musicas.h"

/*---------------- GLOBAIS ----------------*/

volatile int SELECT_IDX_PLAYLIST = 0;
volatile int init_state = 0;
volatile int apena_1_vez = 1;

/* flag */

// Inicializa música funcionando (1) e SELECT não pressionado
volatile char but_START_PAUSE_flag = 1; 
volatile char but_SELECT_flag = 0; 
volatile char init_screen = 1;


/*---------------- CALLBACKS ----------------*/

void but_init(void){
	if(get_init() == 0 && init_screen == 1){
		init_screen = 0;
	}
}

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
	pmc_enable_periph_clk(INIT_PIO_ID);
	pmc_enable_periph_clk(START_PIO_ID);
	pmc_enable_periph_clk(SELECT_PIO_ID);
	
	// ----- Configurando PINOS -----
	pio_set_output(BUZZER_PIO, BUZZER_PIO_IDX_MASK, 1, 0, 0);
	
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

int get_init(){
	return pio_get(INIT_PIO,PIO_INPUT,INIT_PIO_IDX_MASK);
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
		clear_led();
		delay_us(periodo_ms*500);           // (delay_ms *10^(3))/2 = delau_us
		clear_buzzer();
		set_led();
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
		//desenha_progresso(thisNote, notes);
		
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
			//limpa_progresso();
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
	gfx_mono_draw_filled_rect(10,5, 10,12, GFX_PIXEL_CLR);
}

void limpa_nome(){
	gfx_mono_draw_filled_rect(48,6,86,10, GFX_PIXEL_CLR);
}

void desenha_botao_pause(){
	//limpa_estado();
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
	
	//limpa_estado();
	limpa_pause();
		
	gfx_mono_generic_draw_vertical_line(10, 5, 12, GFX_PIXEL_SET );
	gfx_mono_generic_draw_vertical_line(12, 6, 10, GFX_PIXEL_SET );
	gfx_mono_generic_draw_vertical_line(14, 7, 8, GFX_PIXEL_SET );
	gfx_mono_generic_draw_vertical_line(16, 8, 6, GFX_PIXEL_SET );
	gfx_mono_generic_draw_vertical_line(18, 9, 4, GFX_PIXEL_SET );
	gfx_mono_generic_draw_vertical_line(20, 10, 2, GFX_PIXEL_SET );
	
}

void desenha_nome_musica(music playlist[]){
	
	char str_music_idx[128];
	char * nome = playlist[SELECT_IDX_PLAYLIST+1].name;
	
	limpa_nome();
		
	sprintf(str_music_idx, "%d: ", SELECT_IDX_PLAYLIST + 1);
	gfx_mono_draw_string(str_music_idx, 36, 8, &sysfont);
	gfx_mono_draw_string(nome, 48 , 8, &sysfont);
}

void limpa_tudo(){
	gfx_mono_draw_filled_rect(0,0, 128,32, GFX_PIXEL_CLR);
}

void anima_init(){
	
	for(int i = 0 ; (i<128 && init_screen) ; i++){
		
		if(i>0){
			gfx_mono_draw_filled_rect(i-1,7,2,2, GFX_PIXEL_CLR);
		}
			
		delay_ms(50);
		gfx_mono_draw_string(".", i , 3, &sysfont);
	
		if(i == 127){
			i = 0;
		}
		
	}
	
}

void tela_inicio(){
	limpa_tudo();
	gfx_mono_draw_string("-- PLAY THE MUSIC --", 3, 20, &sysfont);
	anima_init();
	
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
	
	// Tela de inicio
	tela_inicio();
	
	/* Insert application code here, after the board has been initialized. */
	while(1) {
		
		// Musica selecionada
		music song = playlist[SELECT_IDX_PLAYLIST];
		
		if(!init_screen){
			
			if(apena_1_vez){
				limpa_tudo();
				apena_1_vez = 0;
			}
			
			if(but_START_PAUSE_flag && !but_SELECT_flag){
				desenha_nome_musica(song.name);
				desenha_botao_play();
				play(song);
			}
			
			if(!but_START_PAUSE_flag){
				desenha_botao_pause();
			}
			
			
			if(but_SELECT_flag){
				desenha_nome_musica(song.name);
				
				init_state = 0;
				but_SELECT_flag = 0;
			}
			
		}
			
	}
}