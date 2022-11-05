
/*
 * configuracoes.h
 *
 * Created: 31/08/2022 17:27:36
 *  Author: Leticia
 */ 


/*-------------------------------------------*/
/*----------------- DEFINES -----------------*/
/*-------------------------------------------*/
#ifndef CONFIGURACOES_H
#define CONFIGURACOES_H
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

/*-------------------------------------------*/
/*---------------- PROTÓTIPOS ---------------*/
/*-------------------------------------------*/

// Função de configuração dos pinos
void io_init();

// Retorna status do botão START (1/0)
int get_startstop();

// Retorna status do botão SELECAO (1/0)
int get_selecao();

// Botao de tela de inicio (But3)
int get_init();

//  Animação de inicio
void anima_init();

// Função tela de inicio
void tela_inicio();
#endif