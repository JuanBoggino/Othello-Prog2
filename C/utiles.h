#ifndef UTILES_H
#define UTILES_H

#include "structs.h"

// coordenada_a_numero Char -> int
// Convierte 'A' -> 0, 'B' -> 1, etc. 
int coordenada_a_numero(char c);

//printea_tablero: Tablero -> None
//Muestra el tablero con coordenadas
void printea_tablero(char tablero[8][8]);

//archivo_salida_final: Tablero, Char, String(path) -> File
//Crea el archivo con el tablero ya acomodado en el path especificado
void archivo_salida_final(char tablero[8][8], char siguiente_color, const char *ruta_archivo_salida);

// indice a letra: Int -> Char
// Mapea los indices de las coordenadas del tablero a sus letras correspondientes
char indice_a_letra(int indice);

#endif
