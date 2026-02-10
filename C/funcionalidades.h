#ifndef FUNCIONALIDADES_H
#define FUNCIONALIDADES_H

#include "structs.h"

// obtener_piezas_voltear: Coordenada, Tablero, Char -> ResultadoCaptura
//Dada una movida, estado del tablero, color de las piezas que mueven, 
//devuelve un struct con el array de coordenadas de piezas que seran volteadas al ejecutar el movimiento
ResultadoCaptura obtener_piezas_a_voltear(Coordenada movida, char tablero[8][8], char color);

//movimiento_legal Coordenada, Tablero, Char('N' o 'B') -> Bool
//Dado un movimiento y el estado del tablero, devuelve 1 si es posible ejecutar el movimiento,
// devuelve 0 en caso de movimiento ilegal

int movimiento_legal(Coordenada movida, char tablero[8][8], char color);

// Coordenada, Tablero, Char("N" o "B")
// Si dada una movida, esta implica voltear piezas rivales, la funcion cambia los colores de las piezas afectadas
void ejecuta_movimiento(Coordenada movida, char tablero[8][8], char color);


// obtener_jugador_por_turno: Array of struct, int -> Jugadores.
// Dado el numero del turno, indica a que jugador le toca mover
Jugadores obtener_jugador_por_turno(Jugadores jugadores[2], int turno);


#endif
