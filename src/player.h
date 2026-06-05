#ifndef PLAYER_H
#define PLAYER_H

#include <gb/gb.h>
#include <stdint.h>

// Variables globales del jugador
extern uint8_t player_x;
extern uint8_t player_y;

// Funciones del jugador
void setup_player(void);
void update_player(void);

#endif