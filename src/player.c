#include "player.h"

// Manejo de Sub Pixeles
uint16_t player_x_fixed = 80 * 16;
uint16_t player_y_fixed = 80 * 16;
uint16_t floor_y_fixed = 136 * 16;

// Variables de físicas
int16_t velocity_y = 0;

// Gravedad = 4 (equivale a 0.25 píxeles por frame)
// Fuerza de salto = -64 (equivale a -4.0 píxeles por frame)
// Esto genera una parábola suave de 32 píxeles de altura
int16_t gravity = 4;
int16_t jump_strength = -64;

// Variables globales
uint8_t player_x = 80;
uint8_t player_y = 136;

void setup_player(void) {
    set_sprite_tile(0, 0); 
    set_sprite_tile(1, 0); 
    move_sprite(0, player_x, player_y);
    move_sprite(1, player_x + 8, player_y);
}

void update_player(void) {
    uint8_t keys = joypad();

    // Movimiento Horizontal (Modificar Lento < 16, Rapido > 16, Dejar normal = 16)
    if (keys & J_LEFT) {
        player_x_fixed -= 14; 
    }
    if (keys & J_RIGHT) {
        player_x_fixed += 14;
    }

    // Límites de pantalla
    if (player_x_fixed < (8 * 16)) player_x_fixed = (8 * 16);
    if (player_x_fixed > (152 * 16)) player_x_fixed = (152 * 16);

    // Salto
    if ((keys & J_A) && (player_y_fixed >= floor_y_fixed)) {
        velocity_y = jump_strength; 
    }

    // Gravedad y posición vertical
    player_y_fixed += velocity_y; 
    
    if (player_y_fixed < floor_y_fixed) {
        velocity_y += gravity; 
    }

    // Velocidad límite
    if (velocity_y > 48) {
        velocity_y = 48;
    }
    
    // Colisión con suelo
    if (player_y_fixed >= floor_y_fixed) {
        player_y_fixed = floor_y_fixed; 
        velocity_y = 0;     
    }

    player_x = player_x_fixed / 16;
    player_y = player_y_fixed / 16;

    // Dibujar en pantalla
    move_sprite(0, player_x, player_y);
    move_sprite(1, player_x + 8, player_y);
}