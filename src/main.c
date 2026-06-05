#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdio.h> 
#include <stdint.h>
#include "player.h"

// Bloque sólido de 8x16
const unsigned char square_data[] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

void main(void)
{
    SPRITES_8x16;

    // Carga de bloque a memoria
    set_sprite_data(0, 2, square_data);
    setup_player(); 

    // Texto en pantalla
    gotoxy(1, 3);
    printf("PIPU EN MOVIMIENTO");

    SHOW_BKG;     // Mostrar Fondo
    SHOW_SPRITES; // Mostrar Sprites
    DISPLAY_ON; 

    // Bucle del juego
    while(1) {
        
        // Mecánicas del jugador
        update_player();

        wait_vbl_done();
    }
}