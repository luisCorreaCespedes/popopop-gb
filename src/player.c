#include "player.h"

// Posición inicial del Player
uint8_t player_x = 80;  
uint8_t player_y = 72; 

// Velocidad base (1 píxel por frame)
const uint8_t MOVE_SPEED = 1;

void setup_player(void) {
    set_sprite_tile(0, 0); 
    set_sprite_tile(1, 0); 

    move_sprite(0, player_x, player_y);
    move_sprite(1, player_x + 8, player_y);
}

void update_player(void) {
    uint8_t keys = joypad();

    // --- LÓGICA DE 4 DIRECCIONES ---
    
    if (keys & J_UP) {
        if (player_y > 16) {
            player_y -= MOVE_SPEED;
        }
    }
    else if (keys & J_DOWN) {
        if (player_y < 144) {
            player_y += MOVE_SPEED;
        }
    }
    else if (keys & J_LEFT) {
        if (player_x > 8) {
            player_x -= MOVE_SPEED;
        }
    }
    else if (keys & J_RIGHT) {
        if (player_x < 152) {
            player_x += MOVE_SPEED;
        }
    }

    move_sprite(0, player_x, player_y);
    move_sprite(1, player_x + 8, player_y);
}