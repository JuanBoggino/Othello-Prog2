#include <stdio.h>
#include "funcionalidades.h"
#include "structs.h"

//inicializar_tablero: Matriz 8x8 (tablero) -> void
//Itera sobre una matriz 8x8 modificando sus elementos de manera tal que simbolizen la posicion inicial de othello
void inicializar_tablero(char tablero[8][8]) {
    // Llena el tablero con 'X'
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tablero[i][j] = 'X';
        }
    }

    // Coloca las 4 fichas centrales
    tablero[3][3] = 'B';
    tablero[3][4] = 'N';
    tablero[4][3] = 'N';
    tablero[4][4] = 'B';
}


// Muestra el tablero 
void printea_tablero(char tablero[8][8]) {

    printf("\n");
    printf("    A B C D E F G H\n");
    printf("    ---------------\n");

    //Recorre las filas
    for (int i = 0; i < 8; i++) {
        
        //Imprime el numero de fila (i+1) y el separador lateral
        printf("%d | ", i + 1);

        // Recorre las columnas
        for (int j = 0; j < 8; j++) {
            // Imprimime el caracter y un espacio a la derecha
            printf("%c ", tablero[i][j]);
        }

        //Salto de linea al terminar la fila
        printf("\n");
    }
    printf("\n");
}


//determinar_ganador Tablero -> Int
//Itera sobre el tablero para contar la cantidad de piezas que puso cada jugador,
//Printea el color de pieza de quien mas tenga posicionadas

int determinar_ganador(char tablero[8][8]) {
    int conteo_negro = 0;
    int conteo_blanco = 0;

    for (int fila = 0; fila < 8; fila++) {
        for (int columna = 0; columna < 8; columna++) {
            if (tablero[fila][columna] == 'N') {
                conteo_negro++;
            } else if (tablero[fila][columna] == 'B') {
                conteo_blanco++;
        }
      }
    }

    // una vez que el bucle termina, compara los resultados:
    if (conteo_negro > conteo_blanco) {
        printf("Gano el jugador de piezas negras");
        return 0;
    } else if (conteo_blanco > conteo_negro) {
        printf("Gano el jugador de piezas blancas");
        return 0;
    } else {
        printf("Empate");
        return 0;
    }
    
}

// tiene_movimientos_validos: Tablero, Char (N o B) -> Int
// Dado el color del jugador que tiene el turno, itera sobre el tablero
// para evaluar si tiene al menos un movimiento legal

int tiene_movimientos_validos(char tablero[8][8], char color) {
    
    Coordenada prueba;

    // Recorre las casillas del tablero
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            //Si la casilla esta vacia
            if (tablero[i][j] == 'X'){

                prueba.fila = i;
                prueba.columna = j;

                if (movimiento_legal(prueba, tablero, color) == 1) {
                    return 1; // Hay al menos un movimiento legal para hacer
                }  
            }

        }
    }
    
    return 0; // No hay movimientos legales
    }


//termino_partida: Tablero -> Bool
// itera sobre el tablero, si halla una "X", entonces el tablero no esta lleno
//Devuelve 1 si no hay movidas legales (incluye tablero lleno), 0 en caso contrario

int termino_partida(char tablero[8][8]){
    //cantidad de movimientos por jugador
    int mov_negras = tiene_movimientos_validos(tablero, 'N');
    int mov_blancas = tiene_movimientos_validos(tablero, 'B');

    //Si ningun jugador tiene movidas legales
    if (mov_blancas == 0 && mov_negras == 0){
        return 1;
    }
    else{
        return 0;
    }
    
    
};