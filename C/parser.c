#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h" 
#include "utiles.h"

// extractor_informacion_jugadores: String (path) -> Jugadores*
// Lee las dos primeras lineas del archivo y guarda en el formato struct Jugadores el color y nombre asociado a cada jugador.
// Analiza que jugador tiene el primer movimiento, 
// si un jugador tiene el primer movimiento ejecuta_primer_movimiento = 1, si no, 0

// Crea un array con dos structs Jugadores
// Asocia array[0] con Jugador 1, y array[1] con Jugador 2
// Retorna un puntero al array de Jugadores

Jugadores *extrae_informacion_jugadores(const char *ruta_archivo_entrada){

    char buffer[255];

    FILE * archivo_movidas = fopen(ruta_archivo_entrada, "r");

    if (archivo_movidas == NULL){
        printf("No se pudo abrir el archivo");
        return NULL;
    }

    //Reserva memoria para un array de dos struct Jugadores
    Jugadores *jugadores = (Jugadores *)malloc(sizeof(Jugadores) * 2);

    // Solo lee las 2 primeras lineas del archivo
    // la variable i simboliza la linea que se esta leyendo

    for (int i = 0; i < 2;) {

        if (fgets(buffer, sizeof(buffer), archivo_movidas) != NULL) {
            
            char *particion = strtok(buffer, ",\n");

            // Copia la primera string antes de la "," a la seccion 'nombre' del struct Jugadores contenido en el array con indice i
            strcpy(jugadores[i].nombre, particion);
        
            // Asigna la particion despues de la coma a la seccion 'color' del struct
            particion = strtok(NULL, ",\n");
                if (particion != NULL){
                jugadores[i].color = particion[0];
                    }
                else{
                    jugadores[i].color = '?';
                }
        }

        i++;
    }
     
    // Lee la tercera linea (color que comienza), ya que el puntero del archivo esta en la 3era linea en este punto
    // Asocia el color de la primera pieza con el nombre del jugador

    if (fgets(buffer, sizeof(buffer),archivo_movidas) != NULL){

        char color_inicial = buffer[0];

        for(int i = 0; i < 2; i++){
            if (jugadores[i].color == color_inicial){
                jugadores[i].ejecuta_primer_movimiento = 1;
            }

        }
    }

    fclose(archivo_movidas);
    return jugadores;

}


//cargar_todos_los_movimientos: String (path), Int* -> Coordenada*

//guarda las todas las coordenadas de las movidas en un array de structs Coordenada
//modifica el valor de la variable total_jugadas a la cantidad de movimientos hechos en toda la partida 

// 1) recibe el path del archivo a leer y un puntero referenciando un int

// 2) se asigna un espacio de memoria de tamanio fijo (ya que hay una cantidad finita de movimientos posibles)
// que pueda ser ocupado por structs coordenadas

Coordenada* cargar_todos_los_movimientos(const char *ruta_archivo_entrada, int *total_jugadas) {

    FILE *archivo = fopen(ruta_archivo_entrada, "r");
    if (archivo == NULL) {
        *total_jugadas = -1; // no se pudo abrir el archivo
        return NULL;
    }

    char buffer[255];
    // La cantidad maxima de movimientos en una partida es de 60, agrego lugar por si hay turnos omitidos
    int movimientos_maximos = 100;
   
    // RESERVA DE MEMORIA
    // Reserva espacio para 100 posibles movidas
    Coordenada *movimientos = (Coordenada *)malloc(movimientos_maximos * sizeof(Coordenada));

    if (movimientos == NULL) {
        fclose(archivo);
        *total_jugadas = -3; //No habia memoria para asignar
        return NULL; 
    }

    // Guardar coordenadas

    // Ignora las 3 primeras lineas
    for(int i = 0; i < 3; i++) {
        fgets(buffer, sizeof(buffer), archivo);
    }

    // Lee y guarda en el array
    int indice = 0;
    while (fgets(buffer, sizeof(buffer), archivo) != NULL && (indice < movimientos_maximos)) {
        
        //---------
        // como en mi editor de texto, la ultima linea es un salto \n, necesito eliminarlo
        int longitud_movida = strlen(buffer);

        if (longitud_movida > 0 && buffer[longitud_movida - 1] == '\n') {
            buffer[longitud_movida - 1] = '\0';
            longitud_movida--;
        }
        //----------

        // la linea \n\0 pasa a ser \0, de longitud 0
        if (longitud_movida == 0) {
            // Jugada paso de turno (-2)
            movimientos[indice].columna = -2;
            movimientos[indice].fila = -2;
        } else {
            // Jugada normal
            movimientos[indice].columna = coordenada_a_numero(buffer[0]);
            movimientos[indice].fila = buffer[1] - '1';
        }
        indice++;
    }

    fclose(archivo);

    // Paso por referencia a una variable en main
    //cantidad de movimientos hechos
    *total_jugadas = indice;

    return movimientos; // Devuelve el puntero al array
}

// Funcion para liberar la memoria luego de la ejecucion de cargar_todos_los_movimientos

void liberar_movimientos(Coordenada *movimientos){
    if (movimientos != NULL) {
        free(movimientos);
    }
}