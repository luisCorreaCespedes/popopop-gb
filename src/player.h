#ifndef PLAYER_H
#define PLAYER_H

#include <gb/gb.h>
#include <stdint.h>

extern uint8_t player_x;
extern uint8_t player_y;

void setup_player(void);
void update_player(void);

#endif