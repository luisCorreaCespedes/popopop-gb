#include <gb/gb.h>
#include <stdint.h>

const unsigned char square_data[] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

// --- VARIABLES DEL JUGADOR ---
uint8_t player_x = 80;
uint8_t player_y = 136;     // Límite del piso

// --- VARIABLES DE FÍSICA ---
int8_t velocity_y = 0;      // Velocidad vertical actual
uint8_t floor_y = 136;      // Altura del suelo invisible
int8_t gravity = 1;         // Fuerza que tira hacia abajo cada frame
int8_t jump_strength = -8;  // Fuerza inicial del salto (hacia arriba)

void main(void)
{
    SPRITES_8x16;
    set_sprite_data(0, 2, square_data);
    set_sprite_tile(0, 0); 
    set_sprite_tile(1, 0); 

    SHOW_SPRITES;
    DISPLAY_ON;

    while(1) {
        uint8_t keys = joypad();

        // MOVIMIENTO HORIZONTAL
        if (keys & J_LEFT) {
            player_x -= 1;
        }
        if (keys & J_RIGHT) {
            player_x += 1;
        }

        // LÍMITES DE PANTALLA
        if (player_x < 8) {
            player_x = 8;
        }
        if (player_x > 152) {
            player_x = 152;
        }

        // SALTO (Botón A)
        if ((keys & J_A) && (player_y >= floor_y)) {
            velocity_y = jump_strength; 
        }

        // FÍSICAS
        player_y += velocity_y; // Sumamos la velocidad a la posición real

        if (player_y < floor_y) {
            // Si estamos en el aire, la gravedad hace efecto
            velocity_y += gravity; 
        }

        // COLISIÓN CON EL SUELO
        if (player_y >= floor_y) {
            player_y = floor_y;
            velocity_y = 0;
        }

        // DIBUJAR SPRITES
        move_sprite(0, player_x, player_y);
        move_sprite(1, player_x + 8, player_y);

        wait_vbl_done();
    }
}