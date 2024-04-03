#include "juego.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <ctime>

using namespace std;

void mostrar(const tJuego& juego) {
	mostrar(juego.tablero);
}

bool cargar(tJuego& juego, string nombre) {
	ifstream archivo;
	archivo.open(nombre+".txt");
	bool exito;
	if (archivo.is_open()) {
		exito = true;
		juego.estado = JUGANDO;
		cargar(juego.tablero, archivo);
	}
	else {
		exito = false;
	}
	
	return exito;
}
void ejecutarMovimiento(tJuego& juego) {
	int col;
	int fila;
	tMovimiento mov = leeMovimiento(juego.tablero, fila, col);
	movimientoFicha(juego.tablero, fila, col, mov);
	actualizaEstado(juego);
}
void actualizaEstado(tJuego& juego) {
	if (ganador(juego)) {
		juego.estado = GANADOR;
	}
	else {
		bool movimientos = hayMovimientos(juego);
		if (movimientos) {
			juego.estado = JUGANDO;
		}
		else {
			juego.estado = BLOQUEO;
		}
	}
}
bool ganador(const tJuego& juego) {
	int numFichas = 0;
	bool valido = false;
	for (int i = 0; i < juego.tablero.fila; i++) {
		for (int j = 0; j < juego.tablero.columna; j++) {
			if (juego.tablero.tCeldaArray[i][j] == FICHA) {
				numFichas += 1;
			}
		}
	}

	if (numFichas == 1 && juego.tablero.tCeldaArray[juego.tablero.fMeta][juego.tablero.cMeta] == FICHA) {
		valido = true;
	}
	return valido;
}
bool hayMovimientos(const tJuego& juego) {
	int fila = 0;
	int columna = 0;
	tMovimientoLista posibles;
	bool movimientos = false;
	while ((!movimientos) && (fila < juego.tablero.fila) && (columna < juego.tablero.columna)) {
		movimientos = movimientosPosibles(juego.tablero, fila, columna, posibles);
		columna += 1;
		if (columna == juego.tablero.fila) {
			columna = 0;
			fila += 1;
		}
	}

	return movimientos;
}

void generar(tJuego& juego, int pasos) {
	srand(time(NULL));

    int fila = FILS;
    int columna = COLS;

	juego.estado = JUGANDO;
	reseteaTablero(juego.tablero, fila, columna);
	int cMeta = (0 + rand() % (columna - 0));
	int fMeta = (0 + rand() % (fila - 0));
	juego.tablero.cMeta =  cMeta;
	juego.tablero.fMeta = fMeta;
	juego.tablero.tCeldaArray[fMeta][cMeta] = FICHA;
	int count = 0;
	while (count < pasos && movimientoInverso(juego)) {
		mostrar(juego);
		count += 1;
	}
}

bool movimientoInverso(tJuego& juego) {
	int fila;
	int col;
	tMovimiento mov;
	fichaAleatoria(juego.tablero, fila, col);

	bool hayOpcion = eligeMovimientoInverso(juego.tablero, fila, col, mov);

	if (hayOpcion) {
		realizaMovimientoInverso(juego.tablero, fila, col, mov);
	}
	return hayOpcion;
}
