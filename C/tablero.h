#ifndef TABLERO_H
#define TABLERO_H

//inicializar_tablero: Matriz 8x8 (tablero) -> void
//dada una matriz de 8x8, la funcion modifica sus elementos en la posicion inicial de othello
//'X' son las casillas vacias, B y N las piezas
void inicializar_tablero(char tablero[8][8]);

//tiene_movimientos_validos: Tablero, Char ('N' o 'B')
// Analiza si un jugador tiene al menos un movimiento legal

int tiene_movimientos_validos(char tablero[8][8], char color);

// determinar_ganador: Tablero -> Int
// Anteriormente habiendo confirmado si el tablero esta lleno, cuenta que jugador tiene mas piezas colocadas,
//printea en pantalla el ganador, retorna 0

int determinar_ganador(char tablero[8][8]);

//termino_partida: Tablero -> Bool
//Devuelve 1 si el tablero esta lleno de piezas, 0 en caso contrario
int termino_partida(char tablero[8][8]);

// Muestra el tablero con formato
void printea_tablero(char tablero[8][8]);

#endif