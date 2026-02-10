#include <stdio.h>
#include "structs.h"
// obtener_jugador_por_turno: Array of struct, int -> Jugadores (info de un jugador).

// La funcion toma un array de structs Jugadores
// y el entero que representa la cantidad de movidas hasta el actual momento del juego.
// el struct con la informacion del jugador 1 se guarda en el indice 0 del array, la del jugador 2 en el indice 1.
// 

Jugadores obtener_jugador_por_turno(Jugadores jugadores[2], int turno) {
    
    // Necesito saber que jugador (1 o 2) (indice del array 0 o 1) es el que empieza
    // si ejecuta_primer_movimiento = 1, ese jugador comienza la partida, caso contrario 0

    int indice_jugador_inicial;
    int indice_otro_jugador;

    if (jugadores[0].ejecuta_primer_movimiento == 1) {
        indice_jugador_inicial = 0;
        indice_otro_jugador = 1;
    } else {
        indice_jugador_inicial = 1;
        indice_otro_jugador = 0;
    };

    if (turno % 2 == 0) {   // Turno par, juega el que ejecuta el primer movimiento
        return jugadores[indice_jugador_inicial];

    } else {
        // Turno impar, juega el otro jugador
        return jugadores[indice_otro_jugador];
    };
};



// obtener_piezas_voltear: Coordenada, Tablero, Char -> ResultadoCaptura

// La funcion toma las coordenadas de un movimiento a intentar, el estado del tablero y el color de las piezas que intentan ese movimiento
// Busca en las 8 direcciones si hay alguna pieza del rival "encerrada", en caso de que la haya, almacena las coordenadas de la pieza del rival
// a voltear en un array de coordenadas, ademas lleva un contador de cuantas piezas van a ser volteadas.

ResultadoCaptura obtener_piezas_a_voltear(Coordenada movida, char tablero[8][8], char color_actual) {
    
    ResultadoCaptura resultado;
    resultado.contador = 0; // contador de volteadas
    
    // Array de 8 direcciones

    int direcciones[8][2] = {
        {-1, 0},   // Vertical: arriba 
        {-1, 1},   // Diagonal: arriba-derecha 
        {0, 1},    // Horizontal: derecha 
        {1, 1},    // Diagonal: abajo-derecha 
        {1, 0},    // Vertical: abajo 
        {1, -1},   // Diagonal: abajo-izquierda 
        {0, -1},   // Horizontal: izquierda 
        {-1, -1}   // Diagonal: arriba-izquierda 
    };

    char color_rival;

    if (color_actual == 'B'){
        color_rival = 'N';
    }
    else{
        color_rival = 'B';
    };
    
    // recorre las 8 direcciones
    for (int i = 0; i < 8; i++) {

        int cambio_fila = direcciones[i][0]; 
        int cambio_columna = direcciones[i][1];
        
        int fila = movida.fila + cambio_fila;
        int col = movida.columna + cambio_columna;
        
        // Array temporal de coordenadas para guardar las piezas rivales halladas en dicha direccion
        // no se pueden capturar mas de 8 piezas con un movimiento 
        Coordenada temp_capturas[8]; 
        int temp_contador = 0;

        // Busca fichas rivales consecutivas sin salirse de los limites del tablero
        
        while (fila >= 0 && fila < 8 && col >= 0 && col < 8 && tablero[fila][col] == color_rival) {
            
            // Guarda la coordenada en el array temporal
            // temp_contador coincide exactamente con el indice del array a guardar la coordenada

            temp_capturas[temp_contador].fila = fila;               
            temp_capturas[temp_contador].columna = col;
            temp_contador++;
            
            // Avanza al siguiente espacio en la misma direccion
            fila += cambio_fila;     
            col += cambio_columna;
        };

        // Verifica si la direccion se cierra con una ficha propia, es decir
        // si encuentra al menos 1 ficha rival, el siguiente espacio es una ficha propia y esta dentro de los limites

        if (temp_contador > 0 && fila >= 0 && fila < 8 && col >= 0 && col < 8 && tablero[fila][col] == color_actual) {
            
            // Copia capturas al array final
            // si la direccion se cierra con una pieza propia,todas las piezas en temp_capturas son validas.

            for (int j = 0; j < temp_contador; j++) {
                // Copia las coordenadas de temp_capturas al array final (resultado.capturadas)
                resultado.capturadas[resultado.contador] = temp_capturas[j];
                resultado.contador++;
            }
        }
    };
    
    return resultado; // Devuelve el struct con todas las capturas de todas las direcciones
};

//movimiento_legal Coordenada, Tablero, Char('N' o 'B') -> Bool
//Dado un movimiento y el estado del tablero, devuelve 1 si es posible ejecutar el movimiento,
// devuelve 0 en caso de movimiento ilegal

int movimiento_legal(Coordenada movida, char tablero[8][8], char color_actual){

    // verificacion casilla fuera de limites.
    if (movida.fila > 7 || movida.columna > 7 || movida.fila < 0 || movida.columna < 0){ 
        return 0; 
    };

    // verificacion casilla ya ocupada
    if (tablero[movida.fila][movida.columna] != 'X'){ 
        return 0;
    };

    // Si al menos una pieza del rival se puede voltear, la movida es valida
    if (obtener_piezas_a_voltear(movida, tablero, color_actual).contador != 0){
        return 1;
    } ;
    
    return 0;
};

//ejecuta_movimiento: Coordenada, Tablero, Char ("N" o "B") -> None
//Dado el array con todas las casillas de las piezas rivales a voltear,
//Modifica el trablero cambiando el color de las piezas que estan en dicho array

void ejecuta_movimiento(Coordenada movida, char tablero[8][8], char color_actual) {
    
    // Obtencion de las capturas
    // Se verifica en main si la movida es legal.
    ResultadoCaptura resultado = obtener_piezas_a_voltear(movida, tablero, color_actual);

    // Posiciona la pieza en la casilla.
    tablero[movida.fila][movida.columna] = color_actual;

    // voltea las piezas capturadas recorriendo el array 'capturadas' (dentro de resultado) usando el contador.

    for (int i = 0; i < resultado.contador; i++) {
        
        int fila_capturada = resultado.capturadas[i].fila;
        int columna_capturada = resultado.capturadas[i].columna;
        
        // Cambia el color de la ficha, es decir, la voltea.
        tablero[fila_capturada][columna_capturada] = color_actual;
    }
}

