from bot import *
from tablero import * 
from reglas import *


def tablero_inicial():
    tablero = []
    for i in range(8):
        fila = []
        for j in range(8):
            fila.append('X')
        tablero.append(fila)

    tablero[3][3] = 'B'
    tablero[3][4] = 'N'
    tablero[4][3] = 'N'
    tablero[4][4] = 'B'

    return tablero


def tablero_lleno():
    """Tablero completamente lleno (ej: 32 N, 32 B)."""
    tablero = []
    for i in range(8):
        fila = []
        for j in range(8):
            if (i + j) % 2 == 0:
                fila.append('N')
            else:
                fila.append('B')

        tablero.append(fila)
    return tablero

def obtener_casillas_vacias(tablero):
    """Auxiliar para generar el set de casillas vacias"""
    vacias = set()
    for i in range(8):
        for j in range(8):
            if tablero[i][j] == 'X':
                vacias.add((i, j))
    return vacias


def test_coordenada_a_indice():
    """Verifica la conversion de letra a indice de columna."""
    assert coordenada_a_indice('A') == 0
    assert coordenada_a_indice('H') == 7
    assert coordenada_a_indice('c') == 2


def test_indice_a_coordenada():
    """Verifica la conversion de fila/columna a coordenada (ej. 'A1')."""
    assert indice_a_coordenada(0, 0) == 'A1'
    assert indice_a_coordenada(7, 7) == 'H8'
    assert indice_a_coordenada(3, 4) == 'E4'


def test_verifica_tablero_lleno():
    """Verifica si la funcion detecta un tablero lleno o no."""
    
    assert verifica_tablero_lleno(tablero_inicial()) == False
    assert verifica_tablero_lleno(tablero_lleno()) == True




def test_cambiar_turno():
    """Verifica el cambio de color de turno."""
    assert cambiar_turno('B') == 'N'
    assert cambiar_turno('N') == 'B'


def test_obtener_pieza_por_turno():
    """Verifica la asignacion de color segun el turno (par/impar)."""
    # Humano es N
    assert obtener_pieza_por_turno('N', 0) == 'N' # Turno 0 (par), Humano
    assert obtener_pieza_por_turno('N', 1) == 'B' # Turno 1 (impar), PC



def test_aplicar_jugada():
    """Verifica que la pieza se coloque y las piezas rivales se volteen correctamente."""
    
    tablero = tablero_inicial()
    
    # Jugada: D3 (3,2) para 'N'. Voltea (3, 3) 'B'.
    movida = (3,2)
    
    color = 'N'
    nuevo_tablero = aplicar_jugada(tablero, movida, color)
    
    # La casilla de la jugada se actualiza
    assert nuevo_tablero[3][2] == 'N'
    
    # La pieza volteada se actualiza
    assert nuevo_tablero[3][3] == 'N' # Antes era 'B'


def test_obtener_jugadas_validas():
    """
    
    """
    tablero = tablero_inicial() # Tiene las 4 fichas centrales
    vacias = obtener_casillas_vacias(tablero)
    
    # Devuelve lista de tuplas ((fila,col), cantidad de volteadas)
    jugadas_info = obtener_jugadas_y_puntaje(tablero, 'N', vacias)
    
    # Extrae solo las coordenadas
    coordenadas_validas = []
    
    for info in jugadas_info:
        jugada_coord = info[0] # El primer elemento es (fila, col)
        coordenadas_validas.append(jugada_coord)

    # Como primer movimiento las negras pueden jugar en:
    # D3 (3,2), C4 (2,3), F5 (5,4), E6 (4,5)
    assert len(coordenadas_validas) == 4
    assert (3, 2) in coordenadas_validas
    assert (2, 3) in coordenadas_validas
    assert (5, 4) in coordenadas_validas
    assert (4, 5) in coordenadas_validas


def test_obtener_jugadas_validas_tablero_bloqueado():
    # Un tablero donde no hay movimientos validos (ej. lleno)
    tablero = tablero_lleno()
    vacias = obtener_casillas_vacias(tablero)

    jugadas_validas = obtener_jugadas_y_puntaje(tablero, 'N', vacias)
    assert len(jugadas_validas) == 0


def test_cambiar_turno():
    assert cambiar_turno("B") == "N"
    assert cambiar_turno("N") == "B"


def test_validar_jugada():

    tablero = tablero_inicial()

    #Mover A1 en un tablero inicial
    assert validar_jugada((0,0), tablero, 'N') == False
    #Mover E7 tablero inicial
    assert validar_jugada((4,6), tablero, 'N') == False
    #Mover D3 tablero inicial (valido siendo negras)
    assert validar_jugada((3,2), tablero, 'N') == True
    #Mover E6 tablero inicial (valido siendo negras)
    assert validar_jugada((4,5), tablero, 'N') == True
    

    
