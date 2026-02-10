import random

from reglas import obtener_jugadas_y_puntaje


def pc_nivel_0(tablero, color_pc, casillas_vacias):
    """
    La PC elige una jugada valida al azar.
    Devuelve (fila, col) o None si no hay jugadas validas.
    Args:
        tablero (matriz 8x8):
        color_pc (char): Color de las piezas que usa la pc ('N' o 'B')
        casillas_vacias (set): Conjunto con las coordenadas de las casillas disponibles

    Returns:
        Tupla (movida): Tupla de 2 enteros que representan las coordenadas del tablero a mover
    """

    #lista con tuplas (coordenada, cantidad_capturas)
    jugadas_validas = obtener_jugadas_y_puntaje(tablero, color_pc, casillas_vacias)

    if len(jugadas_validas) == 0:
        return None   # no puede jugar

    # elige jugada aleatoria
    jugada = random.choice(jugadas_validas)

    return jugada[0] # Coordenada (primer elemento tupla)




def pc_nivel_1(tablero, color_pc, casillas_vacias):
    """
    La PC elige la jugada valida que voltea el maximo de piezas rivales.
    Devuelve (fila, col) o None si no hay jugadas validas.

    Args:
        tablero (matriz 8x8):
        color_pc (char): Color de las piezas que usa la pc ('N' o 'B')
        casillas_vacias (set): Conjunto con las coordenadas de las casillas disponibles

    Returns:
        Tupla (movida): Tupla de 2 enteros que representan las coordenadas del tablero a mover
    """
    
    #info_movimiento: lista de tuplas (Jugada valida, Cantidad de piezas volteadas por la jugada)
    info_movimiento = obtener_jugadas_y_puntaje(tablero, color_pc,casillas_vacias)

    if info_movimiento == []:
        return None
    
    max_volteadas = -1
    
    # Lista para guardar todas las jugadas que dan el mismo maximo
    mejores_opciones = []

    for movida, puntos in info_movimiento:
          
        if puntos > max_volteadas:
            #si encuentra un nuevo maximo reinicia la lista de mejores opciones.
            max_volteadas = puntos
            mejores_opciones = [movida]
        
        elif puntos == max_volteadas:
            #si es un empate con el maximo actual agrega la jugada
            mejores_opciones.append(movida)
            
    # Si hay varias jugadas que voltean el mismo numero maximo de piezas,
    # elige una de ellas al azar 

    if mejores_opciones != []:
        return random.choice(mejores_opciones)
   
