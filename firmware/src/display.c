
/*
 * display.c
 *
 * Created: 10/09/2022 14:47:27
 *  Author: Leticia
 */ 

/*-------------------------------------------*/
/*---------------- INCLUDES -----------------*/
/*-------------------------------------------*/

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

#include "musica.h"
#include "display.h"

/*-------------------------------------------*/
/*----------------- FUNCOES -----------------*/
/*-------------------------------------------*/

void limpa_progresso(){
	gfx_mono_draw_filled_rect(2,20, PROGRESS_WIDTH+6, PROGRESS_HEIGHT+4, GFX_PIXEL_CLR);
}

void progresso(int multiplo, int delta){
	gfx_mono_draw_filled_rect(2,23, PROGRESS_WIDTH/delta * multiplo,PROGRESS_HEIGHT, GFX_PIXEL_SET);
	
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

void desenha_nome_musica(music playlist[], int idx){
	
	char str_music_idx[128];
	char * nome = playlist[idx+1].name;
	
	limpa_nome();
	
	sprintf(str_music_idx, "%d: ", idx + 1);
	gfx_mono_draw_string(str_music_idx, 36, 8, &sysfont);
	gfx_mono_draw_string(nome, 48 , 8, &sysfont);
}

void limpa_tudo(){
	gfx_mono_draw_filled_rect(0,0, 128,32, GFX_PIXEL_CLR);
}

void desenha_traco(int x, int y, gfx_mono_color_t color_px){
	gfx_mono_draw_filled_rect(x,y,2,1, color_px);
}