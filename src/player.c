#include "player.h"

// --- ESTADO INICIAL DEL JUGADOR ---
uint8_t player_world_x = 16;  
uint8_t player_y = 128; // Fila 7 (Sobre el suelo)
uint8_t camera_x = 0;   

// --- VARIABLES DE CONTROL DE MOVIMIENTO ---
uint8_t is_moving = 0;   // 1 si está en transición de casilla
uint8_t dest_x = 0;      // Destino X deseado
uint8_t dest_y = 0;      // Destino Y deseado
int8_t move_dir_x = 0;   // Dirección X (-1 izq, 1 der)
int8_t move_dir_y = 0;   // Dirección Y (-1 arr, 1 abj)
uint8_t move_speed = 1;  // Velocidad base
uint8_t is_falling = 0;  // 1 si está cayendo por gravedad (doble velocidad)

// Importamos la info del nivel desde main.c
extern const uint8_t test_map[9][9];
extern uint8_t map_width;

void setup_player(void) {
    set_sprite_tile(0, 0); 
    set_sprite_tile(1, 0); 
    move_sprite(0, player_world_x - camera_x, player_y);
    move_sprite(1, player_world_x - camera_x + 8, player_y);
}

void update_player(void) {
    uint8_t keys = joypad();

    // BLOQUE 1: TOMA DE DECISIONES (Solo ocurre si Pipu está quieto en una casilla)
    if (is_moving == 0) {
        
        // Conversión a índices del array de colisiones
        uint8_t current_col = (player_world_x - 16) / 16;
        uint8_t current_row = (player_y - 16) / 16;

        uint8_t tile_current = test_map[current_row][current_col];
        uint8_t tile_below = (current_row < 8) ? test_map[current_row + 1][current_col] : 1;

        // FÍSICA: GRAVEDAD (Prioridad Máxima)
        if (tile_below == 0 && tile_current != 2) {
            dest_y = player_y + 16;
            move_dir_y = 1;
            move_dir_x = 0;
            is_moving = 1;
            is_falling = 1; // Activa caída rápida
        } 
        // FÍSICA: CONTROLES DE JUGADOR
        else {
            if (keys & J_LEFT) {
                if (current_col > 0 && test_map[current_row][current_col - 1] != 1) {
                    dest_x = player_world_x - 16; 
                    move_dir_x = -1;
                    move_dir_y = 0;
                    is_moving = 1;          
                }
            }
            else if (keys & J_RIGHT) {
                if (current_col < (map_width - 1) && test_map[current_row][current_col + 1] != 1) {
                    dest_x = player_world_x + 16; 
                    move_dir_x = 1;
                    move_dir_y = 0;
                    is_moving = 1;          
                }
            }
            else if (keys & J_UP) {
                uint8_t tile_above = (current_row > 0) ? test_map[current_row - 1][current_col] : 1;
                if (tile_current == 2 || tile_above == 2) {
                    dest_y = player_y - 16;
                    move_dir_y = -1;
                    move_dir_x = 0;
                    is_moving = 1;
                }
            }
            else if (keys & J_DOWN) {
                if (tile_current == 2 || tile_below == 2) {
                    if (tile_below != 1) { // Evita atravesar el suelo sólido
                        dest_y = player_y + 16;
                        move_dir_y = 1;
                        move_dir_x = 0;
                        is_moving = 1;
                    }
                }
            }
        }
    }
    // BLOQUE 2: EJECUCIÓN DEL MOVIMIENTO PIXEL A PIXEL
    else {
        if (move_dir_x != 0) {
            player_world_x += (move_dir_x * move_speed);
            // Detiene a Pipu al llegar justo a la casilla de destino
            if (player_world_x == dest_x) {
                is_moving = 0;  
                move_dir_x = 0;
            }
        }
        else if (move_dir_y != 0) {
            // Aplica velocidad doble si está cayendo
            uint8_t current_speed_y = (is_falling == 1) ? 2 : move_speed;
            player_y += (move_dir_y * current_speed_y);
            
            if (player_y == dest_y) {
                is_moving = 0;  
                move_dir_y = 0;
                is_falling = 0; // Desactiva la caída al tocar suelo
            }
        }
    }

    // BLOQUE 3: CÁMARA LIBRE
    if (player_world_x > 80) camera_x = player_world_x - 80;
    else camera_x = 0;
    if (camera_x > 0) camera_x = 0; // Límite actual en mapa 9x9

    // Renderizado en pantalla aplicando offset de cámara
    uint8_t screen_x = player_world_x - camera_x;
    move_sprite(0, screen_x, player_y);
    move_sprite(1, screen_x + 8, player_y);
}