
from tablero import coordenada_a_indice, indice_a_coordenada

def obtener_piezas_a_voltear(movida, tablero, color_actual):
    """
    movida: (fila, columna). Dada una movida, revisa en las 8 direcciones si esa movida puede encerrar una pieza rival,
    en caso de que lo haga, guarda en una lista las tuplas de coordenadas de las piezas que van a ser volteadas
    Args:
        movida (str): tupla de 2 enteros
        tablero (matriz 8x8): Tablero
        color_actual (char): Letra que representa el color de pieza del jugador que mueve
    """
    piezas_a_voltear = []
    fila_inicio, columna_inicio = movida
    

    direcciones = [
        (-1, 0),   # arriba
        (-1, 1),   # arriba-derecha
        (0, 1),    # derecha
        (1, 1),    # abajo-derecha
        (1, 0),    # abajo
        (1, -1),   # abajo-izquierda
        (0, -1),   # izquierda
        (-1, -1)   # arriba-izquierda
    ]

    # determina color rival
    if color_actual == 'B':
        color_rival = 'N'
    else:
        color_rival = 'B'

    #recorre las 8 direcciones
    i = 0
    while i < 8:

        cambio_fila = direcciones[i][0]
        cambio_columna = direcciones[i][1]

        fila = fila_inicio + cambio_fila
        columna = columna_inicio + cambio_columna

        # Guarda capturas temporalmente
        captura_temp = []
        contador_temp = 0

        # Mientras haya piezas rivales consecutivas
        while (0 <= fila < 8 and 0 <= columna < 8 and tablero[fila][columna] == color_rival):
            
            captura_temp.append((fila, columna))
            contador_temp += 1

            fila += cambio_fila
            columna += cambio_columna

        # Si se cerro con una pieza propia valida la captura
        if (contador_temp > 0 and 0 <= fila < 8 and 0 <= columna < 8 and tablero[fila][columna] == color_actual):
            
            # copia todas las capturas encontradas
            for (fila, columna) in captura_temp:
                piezas_a_voltear.append((fila, columna))

        i += 1  # avanza a la siguiente direccion
        

    return piezas_a_voltear


def validar_jugada(jugada, tablero, color_actual):
    """
    Valida que un movimiento genere capturas
    
    Args:
        jugada (tupla): Tupla de 2 enteros, representa jugada en formato indices
        tablero (matriz 8x8):
        color_actual (Char): color del jugador que ejecuto la movida
    
    Returns:
        Bool: True si es posible ejecutar la movida
    """

    fila = jugada[0]
    columna = jugada[1]

    # La casilla debe estar vacia
    if tablero[fila][columna] != 'X':
        return False

    # Debe generar capturas
    lista_capturas = obtener_piezas_a_voltear(jugada, tablero, color_actual)

    if len(lista_capturas) == 0:
        return False

    return True

def obtener_jugadas_y_puntaje(tablero, color_actual, casillas_vacias):
    """
    Busca en el conjunto de las casillas disponibles (casillas vacias) que jugadas son validas.
    Almacena todas las posibles movidas validas y que cantidad de piezas rivales voltean en una lista,
    si esta es vacia, no hay posibles movimientos
    
    Args:
        Tablero (matriz 8x8):
        color_actual (Char): Color de pieza del jugador que mueve
        casillas_vacias (set): Conjunto con las coordenadas de las casillas disponibles

    Returns:
        (Lista de tuplas): Lista con las tuplas cuyo primer elemento representa el movimiento
        hecho por el jugador, el segundo elemento representa la cantidad de fichas rivales volteadas dado el movimiento  
    
    """
    jugadas_info = []

    for fila,col in casillas_vacias:

        piezas = obtener_piezas_a_voltear((fila,col), tablero, color_actual)
        cantidad = len(piezas)

        if cantidad > 0:
            jugadas_info.append(((fila,col), cantidad))        

    return jugadas_info


def obtener_pieza_por_turno(color_turno_humano, turno):
    """
    Devuelve a que jugador le toca en funcion de la paridad del turno y el color que juega primero
    Args:
        color_turno_humano (char): color con el que juega el humano
        turno (int): Numero de movida

    Returns:
        Char: color de la pieza que usa el jugador del turno actual
    """
    
    if color_turno_humano == "N":
        color_turno_pc = "B"
    else:
        color_turno_pc = 'N'

    if turno % 2 == 0:
        print("Juega el humano")
        return color_turno_humano
    else:
        print("Juega la PC")
        return color_turno_pc;
    

def pide_jugada(tablero, color_actual):
    """
    Pide el movimiento al jugador humano, si es invalido vuelve a pedirlo
    Args:
        tablero (matriz 8x8):
        Char: (color pieza)
    Returns:
        Tupla: Tupla con la movida del jugador en formato indice de array
    """

    while True:
        jugada_str = input("Ingrese jugada: ")

        letra = jugada_str[0].upper()
        numero = jugada_str[1]

        if len(jugada_str) != 2:
            print("Jugada invalida. Debe ser letra + numero (ej: D3)")
            continue

        if letra not in "ABCDEFGH":
            print("Jugada invalida, la letra debe estar entre A y H")
            continue

        if not numero.isdigit():
            print("Jugada invalida, La fila debe ser un numero entero")
            continue

        columna = coordenada_a_indice(jugada_str[0])
        fila = int(jugada_str[1]) - 1
    
        movida = (fila,columna)

        if validar_jugada(movida, tablero, color_actual):
            return (fila, columna) #devuelve las coordenadas del movimiento valido
        
        else:
            print("Jugada invalida, casilla ya ocupada o no genera capturas")



def aplicar_jugada(tablero, movida, color_actual):
    """
    Coloca la pieza y voltea todas las piezas rivales necesarias.
    Modifica el tablero y lo devuelve.
    
    Args:
        tablero (matriz 8x8):
        movida (tupla): Tupla de 2 enteros que representan el indice de la matriz 8x8
        color_actual Char ('N' o 'B'):

    Returns:
        Tablero:
    """
    fila,col = movida

    # Posiciona la pieza
    tablero[fila][col] = color_actual

    # Obtiene capturas
    piezas = obtener_piezas_a_voltear(movida, tablero, color_actual)

    # Voltea las piezas 
    for (fila, columna) in piezas:
        tablero[fila][columna] = color_actual

    return tablero



def cambiar_turno(color):
    if color == "B":
        return "N"
    return "B"    
