#include <gb/gb.h>
#include <stdint.h>
#include "player.h"
#include "enemies.h" // Preparado para el futuro

// --- 1. ASSETS GRÁFICOS (GREYBOXING) ---
const unsigned char sprite_pipu[] = {
    0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF,
    0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF,
    0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF,
    0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF
};

// Índice BKG 128: Vacío / Cielo
const unsigned char bkg_empty[] = {
    0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
    0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00
};

// Índice BKG 129: Sólido (Verde Oscuro)
const unsigned char bkg_solid[] = {
    0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF,
    0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF
};

// Índice BKG 130: Escalera (Verde Claro, a rayas)
const unsigned char bkg_ladder[] = {
    0x00,0x00, 0xFF,0x00, 0x00,0x00, 0xFF,0x00,
    0x00,0x00, 0xFF,0x00, 0x00,0x00, 0xFF,0x00
};

// --- 2. DATOS DEL NIVEL ---
uint8_t map_width = 9; 
uint8_t map_height = 9; 

// MATRIZ LÓGICA DE COLISIONES
// 0 = Vacío, 1 = Bloque Sólido, 2 = Escalera
const uint8_t test_map[9][9] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {1, 1, 1, 2, 1, 1, 0, 0, 0}, 
    {0, 0, 0, 2, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 2, 0, 0, 1, 1, 1}, 
    {0, 0, 0, 2, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 2, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 2, 0, 0, 0, 0, 0}, 
    {1, 1, 1, 1, 1, 1, 1, 1, 1}  
};

// --- 3. FUNCIONES DE RENDERIZADO ---
void render_map(void) {
    uint8_t r, c;
    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
            uint8_t logic_tile = test_map[r][c];
            
            // Traducción: De colisión lógica a gráficos seguros (128+)
            uint8_t visual_tile = 128; 
            if (logic_tile == 1) visual_tile = 129;
            else if (logic_tile == 2) visual_tile = 130;

            uint8_t bkg_x = 1 + (c * 2);
            uint8_t bkg_y = (r * 2);

            // Dibuja bloques de 16x16 usando tiles de 8x8
            set_bkg_tile_xy(bkg_x, bkg_y, visual_tile);
            set_bkg_tile_xy(bkg_x + 1, bkg_y, visual_tile);
            set_bkg_tile_xy(bkg_x, bkg_y + 1, visual_tile);
            set_bkg_tile_xy(bkg_x + 1, bkg_y + 1, visual_tile);
        }
    }
}

// --- 4. BUCLE PRINCIPAL ---
void main(void)
{
    // Carga inicial de Sprites
    SPRITES_8x16;
    set_sprite_data(0, 2, sprite_pipu);
    setup_player(); 
    init_enemies(); // Llamada al esqueleto de enemigos

    // Carga inicial de Fondos (Usando VRAM segura)
    set_bkg_data(128, 1, bkg_empty);  
    set_bkg_data(129, 1, bkg_solid);  
    set_bkg_data(130, 1, bkg_ladder); 
    render_map();

    // Activa la pantalla
    SHOW_BKG;     
    SHOW_SPRITES; 
    DISPLAY_ON;   

    // Bucle del Motor Base
    while(1) {
        update_player(); 
        update_enemies(); // Llamada al esqueleto de enemigos
        move_bkg(camera_x, 0); 
        wait_vbl_done(); 
    }
}