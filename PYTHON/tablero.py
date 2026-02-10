

def extrae_tablero(ruta_tablero):
    """
    Lee un archivo de othello, elimina el caracter '/n' de cada linea.
    Retorna la tupla con el tablero representado como lista de listas
    y el color del jugador que tiene el primer turno
    Args:
        String: (path del archivo)

    Returns:
         Tupla: (tablero_lista, color_turno):
         tablero_lista: lista de listas (tablero representado como matriz 8x8)
         Char: color_turno_humano: ultima linea ddel archivo, representa el color de la pieza a mover
    """
    tablero_en_lista = []
    color_turno_humano = ""
    
    with open(ruta_tablero, 'r') as archivo:
        # Enumera cada linea del archivo
        for indice, linea in enumerate(archivo):
            #Elimina el /n de cada linea
            linea_limpia = linea.rstrip('\n')
            
            if indice < 8:
                #Las primeras 8 lineas representan un sector del tablero
                #Las convierte a lista y guarda 
                tablero_en_lista.append(list(linea_limpia))
                
            elif indice == 8:
                # La novena linea (indice 8) es el color del jugador
                color_turno_humano = linea_limpia.upper()
               

    return tablero_en_lista, color_turno_humano


def printea_tablero(tablero):
    """
    Toma el tablero representado como lista de listas,
    printea en pantalla agregando coordenadas.
    Args:
        tablero (matriz 8x8):

    Returns:
        None:
    """
    print("    A B C D E F G H")
    print("    ---------------")

    for i in range(8):
        fila = tablero[i]

        fila_con_espacios = " ".join(fila)

        print(f"{i + 1} | {fila_con_espacios}")

    return


def verifica_tablero_lleno(tablero):
    """
    Verifica si el tablero esta completo.
     Devuelve True si lo esta, si no False.
    """
    for fila in tablero:

        for casilla in fila:
            if casilla == 'X':
                return False

    return True


def cuenta_piezas(tablero):
    """
    Si el tablero esta lleno, cuenta la cantidad de piezas
    hay de cada jugador en el tablero
    Args:
        tablero (matriz 8x8):
    Returns:
        tupla: Tupla de 2 enteros
    """
    contador_negras = 0
    contador_blancas = 0

   
    for fila in tablero:

        for casilla in fila:

            if casilla == 'N':
                contador_negras += 1

            else:
                contador_blancas += 1

    return contador_negras, contador_blancas

def coordenada_a_indice(jugada_str):
    """
    Dada una letra entre A y H, devuelve A -> 0, B -> 1, etc
    Args:
        jugada_str (str): Jugada en forma A4, B5, C2
    Returns:
        int: Indice que representa cada letra del abecedario
    """
    columnas_por_indice = {'A': 0, 'B': 1, 'C': 2, 'D': 3,'E': 4, 'F': 5, 'G': 6, 'H': 7}

    columna = jugada_str[0].upper()

    return columnas_por_indice[columna]

def indice_a_coordenada(fila, col):
    """
    Dada una una movida en formato (int,int) (indice de array)
    La convierte en su correspondiente coordenada de tablero
    Ej: (0,0 -> A1)
    Args:
        fila (int): Indice de fila 
        columna (int): Indice de columna
    
    Returns:
        str: String de 2 caracteres que representan una coordenada de tablero
    """
    letras = "ABCDEFGH"
    letra = letras[col]
    numero = fila + 1
    return str(letra) + str(numero)
