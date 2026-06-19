#ifndef PLAYER_H
#define PLAYER_H

#include <gb/gb.h>
#include <stdint.h>

// Coordenadas en la cuadrícula (0 a 9 en X, 0 a 8 en Y)
extern uint8_t cursor_col;
extern uint8_t cursor_row;

void setup_player(void);
void update_player(void);

#endif