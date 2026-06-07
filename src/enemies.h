#ifndef ENEMIES_H
#define ENEMIES_H

#include <gb/gb.h>
#include <stdint.h>

// Definimos los tipos de enemigos
#define TYPE_SNAKE 1
#define TYPE_MUSHROOM 2
#define TYPE_BIRD 3

// Límite de enemigos simultáneos en pantalla (ahorra memoria)
#define MAX_ENEMIES 5

// La Estructura Universal
typedef struct {
    uint8_t active;       // 0 = Muerto/Inactivo, 1 = Vivo
    uint8_t type;         // ¿Qué enemigo es? (TYPE_SNAKE, etc.)
    uint16_t x_fixed;     // Posición X (Punto Fijo para sub-píxeles)
    uint16_t y_fixed;     // Posición Y
    int8_t vel_x;         // Velocidad horizontal
    int8_t vel_y;         // Velocidad vertical
    uint8_t sprite_id;    // Qué sprite de hardware usa (0 y 1 son de Pipu)
} Enemy;

// Declaramos las funciones
void setup_enemies(void);
void update_enemies(void);

#endif