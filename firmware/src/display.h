
/*
 * display.h
 *
 * Created: 10/09/2022 14:47:08
 *  Author: Leticia
 */ 


/*-------------------------------------------*/
/*----------------- DEFINES -----------------*/
/*-------------------------------------------*/
#ifndef DISPLAY_H
#define DISPLAY_H
// Progress Bar
#define PROGRESS_WIDTH	120
#define PROGRESS_HEIGHT 6


/*-------------------------------------------*/
/*---------------- FUNCOES ------------------*/
/*-------------------------------------------*/

// limpa barra de progresso
void limpa_progresso();

// constroi e incrementa barra de progresso
void progresso(int multiplo, int delta);

// limpa botao de pause
void limpa_pause();

// limpa botao de play
void limpa_play();

// limpa nome da música
void limpa_nome();

// cria botao de pause
void desenha_botao_pause();

// cria botao de play
void desenha_botao_play();

// escreve nome da musica que esta tocando
void desenha_nome_musica(music playlist[] , int idx);

// limpa tela do display
void limpa_tudo();

// desenha traco da animação (tela de inicio)
void desenha_traco(int x, int y, gfx_mono_color_t color_px);
#endif