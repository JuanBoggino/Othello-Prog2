#ifndef STRUCTS_H
#define STRUCTS_H

// Jugadores
// El struct guarda la string que representa al nombre del jugador,
// El Char ("N" o "B") que representa el color de las piezas del jugador
// El entero (1 o 0) que representa si el jugador tiene el primer movimiento o no
// 1 si tiene el primer movimiento

typedef struct {
    char nombre[30];
    char color;
    int ejecuta_primer_movimiento;
} Jugadores;

//Coordenada
//Guarda la coordenada x e y de una movida

typedef struct {
    int fila;
    int columna;
} Coordenada;


//ResultadoCaptura
// Guarda un array con coordenadas,
// se supone que contador debe guardar la cantidad de coordenadas guardadas

typedef struct {
    Coordenada capturadas[30];
    int contador;
} ResultadoCaptura;

#endif

