#ifndef PARSER_H
#define PARSER_H

#include "funcionalidades.h"
// extractor_informacion_jugadores:
//Lee desde el archivo la informacion de los jugadores y la guarda en un array de structs Jugadores
Jugadores* extrae_informacion_jugadores(const char *ruta_archivo_entrada);

//cargar_todos_los_movimientos: String (path), Int* -> Coordenada*
//guarda las coordenadas de las movidas en forma de indice en un array de structs Coordenada
//modifica el valor de la variable total_jugadas a la cantidad de movimientos hechos en toda la partida 
Coordenada* cargar_todos_los_movimientos(const char *ruta_archivo_entrada, int *total_jugadas);


// Funcion para liberar la memoria luego de la ejecucion de cargar_todos_los_movimientos
void liberar_movimientos(Coordenada *movimientos);

#endif
