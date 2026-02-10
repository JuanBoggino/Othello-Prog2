#include "funcionalidades.h"
#include "parser.h"
#include "utiles.h"
#include "structs.h"
#include "tablero.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

// Declaracion variables globales
char tablero_inicial[8][8];
char tablero_lleno[8][8];

Coordenada movidaC3 = {2, 4}; //C3
Coordenada movidaE7 = {4, 6}; // E7
Coordenada movidaE3 = {4, 2};  // E3
Coordenada movidaD3 = {3, 2};  // D3

//Llena un tablero de piezas
void llenar_tablero_test(char tablero[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) {
                tablero[i][j] = 'N';
            } else {
                tablero[i][j] = 'B';
            }
        }
    }
}


void test_coordenada_a_numero() {
    assert(coordenada_a_numero('A') == 0);
    assert(coordenada_a_numero('C') == 2);
    assert(coordenada_a_numero('Z') == -1);
    printf("test_coordenada_a_numero pasado\n");
}

void test_obtener_jugador_por_turno() {
    Jugadores jugador[2];
    //Jugador 0 empieza
    strcpy(jugador[0].nombre, "A"); 
    jugador[0].ejecuta_primer_movimiento = 1; 
    jugador[0].color = 'N';

    //Jugador 1 tiene el segundo turno
    strcpy(jugador[1].nombre, "B");
    jugador[1].ejecuta_primer_movimiento = 0; 
    jugador[1].color = 'B';

    // Turno 0 (primera jugada) -> debe ser Jugador 0
    assert(obtener_jugador_por_turno(jugador, 0).color == 'N');
    // Turno 1 (segunda jugada) -> debe ser Jugador 1
    assert(obtener_jugador_por_turno(jugador, 1).color == 'B');
    
    printf("test_obtener_jugador_por_turno pasado\n");
}

void test_movimiento_legal() {

    inicializar_tablero(tablero_inicial);

    assert(movimiento_legal(movidaC3, tablero_inicial, 'B') == 1);
    assert(movimiento_legal(movidaC3, tablero_inicial, 'N') == 0);
    assert(movimiento_legal(movidaE7, tablero_inicial, 'B') == 0);
    assert(movimiento_legal(movidaE3, tablero_inicial, 'B') == 1);
    assert(movimiento_legal(movidaD3, tablero_inicial, 'N') == 1);
    printf("test_movimiento_legal pasado\n");
}

void test_termino_partida() {

    inicializar_tablero(tablero_inicial);

    llenar_tablero_test(tablero_lleno);
    assert(termino_partida(tablero_lleno) == 1);
    assert(termino_partida(tablero_inicial) == 0);
    printf("test_termino_partida pasado\n");
}

void test_determinar_ganador() {
    llenar_tablero_test(tablero_lleno);
    
    // alguno de los 2 gano o fue empate
    assert(determinar_ganador(tablero_lleno) == 0);
    printf("test_determinar_ganador pasado\n");
}

//testea que se voltee la cantidad correcta de piezas
void test_obtener_piezas_a_voltear_contador() {
    inicializar_tablero(tablero_inicial);

    assert(obtener_piezas_a_voltear(movidaC3, tablero_inicial, 'B').contador == 1);
    assert(obtener_piezas_a_voltear(movidaD3, tablero_inicial, 'N').contador == 1);
    printf("test_obtener_piezas_a_voltear_contador pasado\n");
}

void test_sin_movimientos() {
    char tablero_bloqueado[8][8];
    // Llena el tablero solo de blancas
    for(int i=0; i<8; i++) 
        for(int j=0; j<8; j++) 
            tablero_bloqueado[i][j] = 'B';

    // Las negras no deberian tener jugadas posibles
    assert(tiene_movimientos_validos(tablero_bloqueado, 'N') == 0);

    printf("test_sin_movimientos pasado\n");
}


int main() {

    printf("Iniciando pruebas\n");
    printf("\n");
    test_coordenada_a_numero();
    test_movimiento_legal();
    test_termino_partida();
    test_determinar_ganador();
    test_sin_movimientos();
    test_obtener_jugador_por_turno();
    test_obtener_piezas_a_voltear_contador();

    printf("\nTodos los tests pasaron exitosamente\n");
    return 0;
}