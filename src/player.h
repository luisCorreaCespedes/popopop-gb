#ifndef PLAYER_H
#define PLAYER_H

#include <gb/gb.h>
#include <stdint.h>

// --- VARIABLES GLOBALES DE JUGADOR ---
// player_world_x: Posición lógica en el mapa completo (no en la pantalla)
extern uint8_t player_world_x;
extern uint8_t player_y;
extern uint8_t camera_x;

// --- PROTOTIPOS DE FUNCIONES ---
void setup_player(void);
void update_player(void);

#endif