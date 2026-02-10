import sys

from tablero import(
extrae_tablero, printea_tablero
,indice_a_coordenada, cuenta_piezas, verifica_tablero_lleno)

from reglas import(
    cambiar_turno, obtener_jugadas_y_puntaje, pide_jugada, aplicar_jugada
)
from bot import(pc_nivel_0, pc_nivel_1)



def jugar_othello(ruta_tablero, nivel_pc, color_humano):
    """
    Bucle principal juego
    """
    #Extrae informacion del tablero inicial
    info_tablero = extrae_tablero(ruta_tablero)
    color_primer_movimiento = info_tablero[1]
    tablero = info_tablero[0]

    color_humano = color_humano.upper()
    color_pc = "B" if color_humano == "N" else "N"

    turno = color_primer_movimiento  #El turno inicial 

    # Conjunto que guarda las casillas vacias ---
    casillas_vacias = set()
    for f in range(8):
        for c in range(8):
            if tablero[f][c] == 'X':
                casillas_vacias.add((f, c))
    # --------------------------

    #Muestra el estado en el que se recibio el tablero
    printea_tablero(tablero)

    # -- Contador de pases de turnos consecutivos, si hay 2 consecutivos se termina el juego --
    pases_consecutivos = 0
    #--------

    #Bucle principal juego
    while True:

        if turno == color_humano:
            print("-----------------------")
            print(f"Turno humano, piezas {turno}")
            print("-----------------------")
            
        else:
            print("-----------------------")
            print(f"Turno PC, piezas {turno}")
            print("-----------------------")

        #Lista con las posibles movidas del jugador
        jugadas_turno = obtener_jugadas_y_puntaje(tablero, turno, casillas_vacias)

        #Si un jugador no puede mover, se pasa el turno
        if len(jugadas_turno) == 0:
            print(f"El jugador {turno} no puede jugar. Pasa el turno.\n")
            printea_tablero(tablero)

            pases_consecutivos += 1

            #Si luego de un turno salteado, se saltea otro mas, termina el juego
            if pases_consecutivos >= 2:
                print("Ambos jugadores se quedaron sin movimientos")
                break

            # cambiar turno y seguir
            turno = cambiar_turno(turno)
            continue

        #Si luego de un turno omitido se pudo jugar
        pases_consecutivos = 0

        #Si hay movidas posibles
        if turno == color_humano:
            movida = pide_jugada(tablero, turno)
            #modifica el tablero
            aplicar_jugada(tablero, movida, turno)

            printea_tablero(tablero)
            print("Humano jugo:", indice_a_coordenada(movida[0], movida[1]))  
            print("\n")

        else:
            if nivel_pc == 0:
                movida = pc_nivel_0(tablero, turno, casillas_vacias)

            elif nivel_pc == 1:
                movida = pc_nivel_1(tablero, turno, casillas_vacias)

            if movida is None:
                print("La PC no tiene jugadas validas. Pasa el turno.\n")
                turno = cambiar_turno(turno)
                continue
            
            #modifica tablero
            aplicar_jugada(tablero,movida,turno)
            
            printea_tablero(tablero)
            print("PC jugo:", indice_a_coordenada(movida[0], movida[1]))
            print("\n")

        #Una vez aplicada la movida, se elimina del conjunto de casillas disponibles
        casillas_vacias.discard(movida)

        # Tablero lleno?
        if verifica_tablero_lleno(tablero):
            print("Tablero completo. Fin del juego.")
            break

       #Cambia el turno
        turno = cambiar_turno(turno)

    # fin, cuenta piezas
    
    contador_piezas = cuenta_piezas(tablero)
    negras = contador_piezas[0]
    blancas = contador_piezas[1]

    print(f"Negras: {negras} | Blancas: {blancas}")

    if negras > blancas:
        print("Ganan las Negras")
    elif blancas > negras:
        print("Ganan las Blancas")
    else:
        print("Empate")

    return tablero


if __name__ == "__main__":
    # Verificacion cantidad de argumentos
    if len(sys.argv) != 4:
        print("Uso: python3 main.py <archivo_tablero> <nivel_bot (0/1)> <color_humano (N/B)>")
        sys.exit(1)

    ruta_archivo = sys.argv[1]

    # El nivel del bot es un numero valido?
    input_nivel = sys.argv[2]
    if input_nivel not in ["0", "1"]:
        print("Uso: python3 main.py <archivo_tablero> <nivel_bot (0/1)> <color_humano (N/B)>")
        print(f"Error: '{input_nivel}' no es un nivel valido. Debe ser 0 o 1.")
        sys.exit(1)

    nivel_pc = int(input_nivel)

    color_humano = sys.argv[3].upper()
    # El tercer argumento es un color valido?
    if color_humano not in ["N", "B"]:
        print("Uso: python3 main.py <archivo_tablero> <nivel_bot (0/1)> <color_humano (N/B)>")
        print(f"Error: '{sys.argv[3]}' no es un color valido. Debe ser 'N' o 'B'.")
        sys.exit(1)
    
    
    
    jugar_othello(ruta_archivo,nivel_pc,color_humano)
