#include "enemies.h"

// Listado de enemigos
Enemy enemies[MAX_ENEMIES];

// Gráficos para un bloque Verde Oscuro de 8x16
const unsigned char enemy_data[] = {
    0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF,
    0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF,
    0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF,
    0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF
};

void setup_enemies(void) {
    // Cargamos los gráficos en la VRAM. 
    // Empezamos en el slot 2 (porque Pipu ya usa el slot 0 y 1)
    set_sprite_data(2, 2, enemy_data);

    // Vaciamos la lista de enemigos al iniciar
    for (uint8_t i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].active = 0;
    }

    // --- SPAWN MANUAL DE PRUEBA ---
    // Hacemos aparecer una serpiente para probar la lógica
    enemies[0].active = 1;
    enemies[0].type = TYPE_SNAKE;
    enemies[0].x_fixed = 120 * 16;  // Empieza más a la derecha
    enemies[0].y_fixed = 136 * 16;  // Mismo suelo que Pipu
    enemies[0].vel_x = -8;          // Velocidad: 0.5 píxeles por frame (izquierda)
    
    // Le asignamos los sprites de hardware 2 y 3
    enemies[0].sprite_id = 2;
    set_sprite_tile(2, 2);
    set_sprite_tile(3, 2);
}

void update_enemies(void) {
    for (uint8_t i = 0; i < MAX_ENEMIES; i++) {
        // Si el enemigo no está activo, saltamos al siguiente
        if (enemies[i].active == 0) continue;

        // IA DE LA SERPIENTE
        if (enemies[i].type == TYPE_SNAKE) {
            
            // Aplicar movimiento horizontal
            enemies[i].x_fixed += enemies[i].vel_x;

            // Colisión básica con los bordes de la pantalla (Rebote)
            if (enemies[i].x_fixed < (8 * 16)) {
                enemies[i].x_fixed = 8 * 16;
                enemies[i].vel_x = 8; // Cambia dirección a la derecha
            }
            if (enemies[i].x_fixed > (152 * 16)) {
                enemies[i].x_fixed = 152 * 16;
                enemies[i].vel_x = -8; // Cambia dirección a la izquierda
            }

            // Dibujar en pantalla
            uint8_t draw_x = enemies[i].x_fixed / 16;
            uint8_t draw_y = enemies[i].y_fixed / 16;
            
            move_sprite(enemies[i].sprite_id, draw_x, draw_y);
            move_sprite(enemies[i].sprite_id + 1, draw_x + 8, draw_y);
        }
    }
}