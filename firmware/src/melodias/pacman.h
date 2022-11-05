
/*
 * pacman.h
 *
 * Created: 04/09/2022 12:32:26
 *  Author: Leticia
 */ 

#include "notes.h"


// change this to make the song slower or faster
#define TIME_PACMAN  105


int pacman_melody[] = {

	// Pacman
	// Score available at https://musescore.com/user/85429/scores/107109
	NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, //1
	NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
	NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,

	NOTE_B4, 16,  NOTE_B5, 16,  NOTE_FS5, 16,   NOTE_DS5, 16,  NOTE_B5, 32,  //2
	NOTE_FS5, -16, NOTE_DS5, 8,  NOTE_DS5, 32, NOTE_E5, 32,  NOTE_F5, 32,
	NOTE_F5, 32,  NOTE_FS5, 32,  NOTE_G5, 32,  NOTE_G5, 32, NOTE_GS5, 32,  NOTE_A5, 16, NOTE_B5, 8
};

#define SIZE_PACMAN sizeof(pacman_melody)