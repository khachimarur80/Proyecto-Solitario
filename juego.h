#ifndef juego_h
#define juego_h

#include "tablero.h"
#include "movimiento.h"
#include <fstream>

using namespace std;

enum tEstado {JUGANDO, GANADOR, BLOQUEO};
typedef struct {
	tTablero tablero;
	tEstado estado;
} tJuego;

void mostrar(const tJuego& juego);
bool cargar(tJuego& juego, string nombre);
void ejecutarMovimiento(tJuego& juego);
void actualizaEstado(tJuego& juego);
bool ganador(const tJuego& juego);
bool hayMovimientos(const tJuego& juego);

void generar(tJuego& juego, int pasos);
bool movimientoInverso(tJuego& juego);
#endif
