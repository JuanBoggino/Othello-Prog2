#include <stdio.h>

// coordenada_a_numero Char -> int
// Convierte 'A' -> 0, 'B' -> 1, etc. (usando aritmetica ASCII)

int coordenada_a_numero(char caracter) {
    if (caracter >= 'A' && caracter <= 'H') {
        return caracter - 'A'; 
    }
    // Si no es una columna valida, devuelve -1
    return -1;
    };

// indice a letra: Int -> Char
// Mapea los indices de las coordenadas del tablero a sus letras correspondientes
char indice_a_letra(int indice) {
    if (indice >= 0 && indice <= 7) {

        return 'A' + indice;
    }
    return '?'; // Caracter de error
}

//archivo_salida_final: Tablero, Char('N' o 'B'), Str (Path archivo) -> void
//Crea el archivo con el tablero ya formateado en el path especificado
void archivo_salida_final(char tablero[8][8],char color_siguiente, const char *ruta_archivo_salida) {
    
    FILE *archivo_salida = fopen(ruta_archivo_salida, "w");
    
    // Recorre el tablero y escribe los caracteres en el archivo.

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            fprintf(archivo_salida, "%c", tablero[i][j]);
        }
        // Agrega un salto de linea al final de cada fila
        fprintf(archivo_salida, "\n"); 
    }

    // escribe en la ultima linea el color de las fichas que tienen la proxima movida
    fprintf(archivo_salida, "%c\n", color_siguiente);

    fclose(archivo_salida);
    printf("Juego finalizado, archivo guardado\n");
};
