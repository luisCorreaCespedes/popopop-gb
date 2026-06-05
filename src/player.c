#include "player.h"

// Variables físicas del jugador
uint8_t player_x = 80;
uint8_t player_y = 136;
int8_t velocity_y = 0;
uint8_t floor_y = 144;
int8_t gravity = 1;
int8_t jump_strength = -8;

// Inicializar jugador en pantalla
void setup_player(void) {
    set_sprite_tile(0, 0); 
    set_sprite_tile(1, 0); 
    move_sprite(0, player_x, player_y);
    move_sprite(1, player_x + 8, player_y);
}

// Actualizar físicas y botones cada frame
void update_player(void) {
    uint8_t keys = joypad();

    // Movimiento del jugador
    if (keys & J_LEFT) {
        player_x -= 1;
    }
    if (keys & J_RIGHT) {
        player_x += 1;
    }

    // Límites de pantalla
    if (player_x < 8) player_x = 8;
    if (player_x > 152) player_x = 152;

    // Salto del jugador
    if ((keys & J_A) && (player_y >= floor_y)) {
        velocity_y = jump_strength; 
    }

    // Gravedad del jugador
    player_y += velocity_y; 
    if (player_y < floor_y) {
        velocity_y += gravity; 
    }
    
    // Colisión con el suelo
    if (player_y >= floor_y) {
        player_y = floor_y; 
        velocity_y = 0;     
    }

    // Mostrar jugador en pantalla
    move_sprite(0, player_x, player_y);
    move_sprite(1, player_x + 8, player_y);
}