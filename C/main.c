#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"         // Para Jugadores, Coordenada, ResultadoCaptura
#include "parser.h"          // Para extrae_informacion_jugadores, extrae_movimiento
#include "funcionalidades.h" // Para obtener_jugador_por_turno, movimiento_legal, etc.
#include "utiles.h"          // Para archivo_salida_final, printea_tablero
#include "tablero.h"         // para inicializar_Tablero, termino_partida, determinar_ganador

int main(int argc, char *argv[]) {

    // Verificacion de argumentos
    if (argc != 3) {
        printf("Uso: <archivo_entrada> <archivo_salida>\n");
        return 1;
    }

    const char *ruta_archivo_entrada = argv[1];
    const char *ruta_archivo_salida = argv[2];

    // Inicializacon tablero inicial
    char tablero[8][8];
    // "Rellena el tablero"
    inicializar_tablero(tablero);


    //
    Jugadores *lista_jugadores = extrae_informacion_jugadores(ruta_archivo_entrada);
    if (lista_jugadores == NULL){
        printf("Fallo de memoria al cargar informacion de los jugadores");
        return 1;
    }

    // -------------------------
    // CARGA DE MOVIMIENTOS 
    // ------------------------
    
    //Se modifica a la cantidad de lineas que representan jugadas--
    int cantidad_total_jugadas = 0;
    //--

    //Guarda las movidas en un array de coordenadas
    Coordenada *lista_movimientos = cargar_todos_los_movimientos(ruta_archivo_entrada, &cantidad_total_jugadas);

    // Manejo de errores basado los codigos (-1 y -3)
    if (lista_movimientos == NULL) {
        
        if (cantidad_total_jugadas == -1) {
            printf("Error: No se pudo abrir el archivo de entrada.\n");
            return 1;
        }
        else if (cantidad_total_jugadas == -3) {
            printf("Error: Memoria insuficiente (fallo malloc).\n");
            return 1;
        }
    }

    // -------------------
    // BUCLE DE JUEGO
    // -------------------

    int turno = 0; //Numero del turno actual e indice para recorrer el array de coordenadas
    // Inicializacion info jugador 
    Jugadores jugador_actual;

    while (1) {
        
        // Determina de quien es el turno
        jugador_actual = obtener_jugador_por_turno(lista_jugadores, turno);

        // verificar si se acabaron las jugadas
        if (turno >= cantidad_total_jugadas) {
            // Fin del archivo: guarda el estado final en el archivo de salida y se finaliza la ejecucion
            archivo_salida_final(tablero, jugador_actual.color, ruta_archivo_salida);
            break; 
        }

        // Obtiene la jugada desde la memoria 
        Coordenada jugada = lista_movimientos[turno];

        //Si fila o columna = -2 se analiza si hay que omitir el turno o es ilegal omitirlo
        if (jugada.fila == -2) {
            
           // si el jugador pasa el turno, pero en realidad tenia al menos un movimiento valido, se considera ilegal
            
            if (tiene_movimientos_validos(tablero, jugador_actual.color) == 1) {
                
                printf("El jugador %s paso el turno pero tenia jugadas validas, fin.\n", jugador_actual.nombre);
                
                // Muestra tablero antes del error y termina
                printea_tablero(tablero);
                
                liberar_movimientos(lista_movimientos); // libera memoria
                free(lista_jugadores);
                return 0; 
            }
            
            // si es verdad que no tenia movimientos validos
         
            turno++;
            continue;
        }

        // Movimiento normal
        if (movimiento_legal(jugada, tablero, jugador_actual.color) == 1) {
            
            ejecuta_movimiento(jugada, tablero, jugador_actual.color);
            turno++; // Avanza a la siguiente coordenada en el array

        } else {
            // Movimiento ilegal, avisa y muestra con el tablero antes de la movida ilegal
            printf("El jugador %s hizo una movida ilegal '%c%d', fin.\n"
                    , jugador_actual.nombre, indice_a_letra(jugada.columna), jugada.fila + 1);
            
            printea_tablero(tablero);

            liberar_movimientos(lista_movimientos); // Libera la memoria 
            free(lista_jugadores);
            return 0; 
        }

        // Verifica si el tablero esta lleno
        if (termino_partida(tablero) == 1){
            printea_tablero(tablero);
            determinar_ganador(tablero);
            
            break;
        }
    }

    // Libera memoria al final del programa
    liberar_movimientos(lista_movimientos);
    free(lista_jugadores);
    
    return 0;
}