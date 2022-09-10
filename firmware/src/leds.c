
/*
 * leds.c
 *
 * Created: 10/09/2022 14:36:18
 *  Author: Leticia
 */ 


/*-------------------------------------------*/
/*---------------- INCLUDES -----------------*/
/*-------------------------------------------*/

#include <asf.h>

#include "leds.h"


/*-------------------------------------------*/
/*----------------- FUNCOES -----------------*/
/*-------------------------------------------*/

void apaga_leds(){
	set_led1();
	set_led2();
	set_led3();
}

void acende_leds(int freq){
	if(freq<150 || freq>1500){
		clear_led1();
		set_led2();
		set_led3();
		}else if(freq < 500  && freq > 250){
		clear_led2();
		set_led1();
		set_led3();
		}else{
		clear_led3();
		set_led1();
		set_led2();
	}
}

void set_led1(){
	pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
}

void clear_led1(){
	pio_clear(LED1_PIO, LED1_PIO_IDX_MASK);
}

void set_led2(){
	pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
}

void clear_led2(){
	pio_clear(LED2_PIO, LED2_PIO_IDX_MASK);
}

void set_led3(){
	pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
}

void clear_led3(){
	pio_clear(LED3_PIO, LED3_PIO_IDX_MASK);
}