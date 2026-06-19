#include "player.h"

// Iniciamos en el centro de la pantalla
// Columnas (0 al 9) | Filas (0 al 8)
uint8_t cursor_col = 4;  
uint8_t cursor_row = 4;  

uint8_t previous_keys = 0;

void setup_player(void) {
    // Sprite 0 usa el Tile 0 (arriba) y el Tile 1 (abajo)
    set_sprite_tile(0, 0); 
    
    // Sprite 1 usa el Tile 2 (arriba) y el Tile 3 (abajo)
    set_sprite_tile(1, 2); 
    
    // Cálculo de posición inicial (Píxeles = Casilla * 16 + Offset de Hardware)
    uint8_t px = (cursor_col * 16) + 8;
    uint8_t py = (cursor_row * 16) + 16;
    
    move_sprite(0, px, py);
    move_sprite(1, px + 8, py);
}

void update_player(void) {
    uint8_t keys = joypad();

    // --- MOVIMIENTO DE CUADRÍCULA ESTRICTO ---
    if ((keys & J_UP) && !(previous_keys & J_UP)) {
        if (cursor_row > 0) cursor_row--;
    }
    else if ((keys & J_DOWN) && !(previous_keys & J_DOWN)) {
        if (cursor_row < 8) cursor_row++; // Máximo 8 filas (144px alto)
    }
    else if ((keys & J_LEFT) && !(previous_keys & J_LEFT)) {
        if (cursor_col > 0) cursor_col--;
    }
    else if ((keys & J_RIGHT) && !(previous_keys & J_RIGHT)) {
        if (cursor_col < 9) cursor_col++; // Máximo 9 columnas (160px ancho)
    }

    previous_keys = keys;

    // --- ACTUALIZACIÓN VISUAL ---
    // Traducimos la coordenada de la cuadrícula a píxeles de pantalla reales
    uint8_t px = (cursor_col * 16) + 8;
    uint8_t py = (cursor_row * 16) + 16;

    move_sprite(0, px, py);
    move_sprite(1, px + 8, py);
}