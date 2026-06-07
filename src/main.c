#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdio.h> 
#include <stdint.h>
#include "player.h"
#include "enemies.h"

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
    setup_enemies();

    // Texto en pantalla
    gotoxy(1, 3);
    printf("TEST ROOM");

    SHOW_BKG;     // Mostrar Fondo
    SHOW_SPRITES; // Mostrar Sprites
    DISPLAY_ON; 

    // Bucle del juego
    while(1) {
        
        // Mecánicas del jugador
        update_player();
        update_enemies();

        wait_vbl_done();
    }
}