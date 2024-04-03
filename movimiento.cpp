#include "movimiento.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <ctime>

using namespace std;

bool fichaBloqueada(const tTablero& tablero, int fila, int col) {
	tMovimiento moverArriba = moviendo(ARRIBA, fila, col);
	tMovimiento moverAbajo = moviendo(ARRIBA, fila, col);
	tMovimiento moverDerecha = moviendo(ARRIBA, fila, col);
	tMovimiento moverIzquierda = moviendo(ARRIBA, fila, col);

	tMovimientoLista posibles;
	posibles.movimientoArray[0] = moverArriba;
	posibles.movimientoArray[1] = moverAbajo;
	posibles.movimientoArray[2] = moverDerecha;
	posibles.movimientoArray[3] = moverIzquierda;
	posibles.pos = 4;

	return !movimientosPosibles(tablero, fila, col, posibles);
}
tMovimiento moviendo(tDireccion dir, int fila, int col) {
	tMovimiento movimiento;
	movimiento.direccion = dir;
	switch (dir) {
		case ARRIBA:
			movimiento.filaDestino = fila - 2;
			movimiento.columnaDestino = col;
			movimiento.filaSaltada = fila - 1;
			movimiento.columnaSaltada = col;
			break;
		case ABAJO:
			movimiento.filaDestino = fila + 2;
			movimiento.columnaDestino = col;
			movimiento.filaSaltada = fila + 1;
			movimiento.columnaSaltada = col;
			break;
		case DERECHA:
			movimiento.filaDestino = fila;
			movimiento.columnaDestino = col + 2;
			movimiento.filaSaltada = fila;
			movimiento.columnaSaltada = col + 1;
			break;
		case IZQUIERDA:
			movimiento.filaDestino = fila;
			movimiento.columnaDestino = col - 2;
			movimiento.filaSaltada = fila;
			movimiento.columnaSaltada = col - 1;
			break;
	}

	return movimiento;
}
tMovimiento leeMovimiento(const tTablero& tablero, int& fila, int& col) {
	tMovimientoLista posibles;

	cout << "Elige fila y columna para mover : ";
	cin >> fila >> col;
	fila -= 1;
	col -= 1;
	while (!movimientosPosibles(tablero, fila, col, posibles)) {
		cout << "Casilla invalida!" << endl;
		cout << "Elige fila y columna para mover : ";
		cin >> fila >> col;
		fila -= 1;
		col -= 1;
	};

	return eligeMovimiento(posibles);
}
bool movimientosPosibles(const tTablero& tablero, int fila, int col, tMovimientoLista& listaMov) {
	bool alguno = false;

	if (tablero.tCeldaArray[fila][col] == FICHA) {
		tMovimiento movimientoArriba;
		tMovimiento movimientoAbajo;
		tMovimiento movimientoDerecha;
		tMovimiento movimientoIzquierda;

		movimientoArriba = moviendo(ARRIBA, fila, col);
		movimientoAbajo = moviendo(ABAJO, fila, col);
		movimientoDerecha = moviendo(DERECHA, fila, col);
		movimientoIzquierda = moviendo(IZQUIERDA, fila, col);

		if (
			valida(tablero, movimientoArriba.filaDestino, movimientoArriba.columnaDestino) &&
			esFicha(tablero, movimientoArriba.filaSaltada, movimientoArriba.columnaSaltada) &&
			esVacia(tablero, movimientoArriba.filaDestino, movimientoArriba.columnaDestino)
			) {
			listaMov.movimientoArray[listaMov.pos] = movimientoArriba;
			listaMov.pos += 1;
			alguno = true;
		}
		if (
			valida(tablero, movimientoAbajo.filaDestino, movimientoAbajo.columnaDestino) &&
			esFicha(tablero, movimientoAbajo.filaSaltada, movimientoAbajo.columnaSaltada) &&
			esVacia(tablero, movimientoAbajo.filaDestino, movimientoAbajo.columnaDestino)
			) {
			listaMov.movimientoArray[listaMov.pos] = movimientoAbajo;
			listaMov.pos += 1;
			alguno = true;
		}
		if (
			valida(tablero, movimientoDerecha.filaDestino, movimientoDerecha.columnaDestino) &&
			esFicha(tablero, movimientoDerecha.filaSaltada, movimientoDerecha.columnaSaltada) &&
			esVacia(tablero, movimientoDerecha.filaDestino, movimientoDerecha.columnaDestino)
			) {
			listaMov.movimientoArray[listaMov.pos] = movimientoDerecha;
			listaMov.pos += 1;
			alguno = true;
		}
		if (
			valida(tablero, movimientoIzquierda.filaDestino, movimientoIzquierda.columnaDestino) &&
			esFicha(tablero, movimientoIzquierda.filaSaltada, movimientoIzquierda.columnaSaltada) &&
			esVacia(tablero, movimientoIzquierda.filaDestino, movimientoIzquierda.columnaDestino)
			) {
			listaMov.movimientoArray[listaMov.pos] = movimientoIzquierda;
			listaMov.pos += 1;
			alguno = true;
		}
	}
	
	return alguno;
}
tMovimiento eligeMovimiento(const tMovimientoLista& listaMov) {
	tMovimiento movimiento;
	if (listaMov.pos == 1) {
		movimiento = listaMov.movimientoArray[0];
	}
	else {
		cout << "Elige entre las siguientes" << listaMov.pos << "opciones : " << endl;
		for (int i = 0; i < listaMov.pos; i++) {
			switch (listaMov.movimientoArray[i].direccion) {
			case ARRIBA:
				cout << "Presione " << i << " para ir ARRIBA" << endl;
				break;
			case ABAJO:
				cout << "Presione " << i << " para ir ABAJO" << endl;
				break;
			case DERECHA:
				cout << "Presione " << i << " para ir DERECHA" << endl;
				break;
			case IZQUIERDA:
				cout << "Presione " << i << " para ir IZQUIERDA" << endl;
				break;
			}
		}
		int opcion;
		cin >> opcion;
		movimiento = listaMov.movimientoArray[opcion];
	}
	return movimiento;
}
void movimientoFicha(tTablero& tablero, int fila, int col, const tMovimiento& mov) {
	tablero.tCeldaArray[fila][col] = VACIA;
	tablero.tCeldaArray[mov.filaSaltada][mov.columnaSaltada] = VACIA;
	tablero.tCeldaArray[mov.filaDestino][mov.columnaDestino] = FICHA;
}

bool eligeMovimientoInverso(const tTablero& tablero, int fila, int col, tMovimiento& mov) {
	tMovimientoLista posibles;
	if (posibleMovimientoInverso(tablero, fila, col, ARRIBA)) {
		tMovimiento movimiento;
		movimiento.direccion = ARRIBA;
		movimiento.filaDestino = fila + 2;
		movimiento.columnaDestino = col;
		movimiento.filaSaltada = fila + 1;
		movimiento.columnaSaltada = col;
		posibles.movimientoArray[posibles.pos] = movimiento;
		posibles.pos += 1;
	}
	if(posibleMovimientoInverso(tablero, fila, col, ABAJO)) {
		tMovimiento movimiento;
		movimiento.direccion = ABAJO;
		movimiento.filaDestino = fila - 2;
		movimiento.columnaDestino = col;
		movimiento.filaSaltada = fila - 1;
		movimiento.columnaSaltada = col;
		posibles.movimientoArray[posibles.pos] = movimiento;
		posibles.pos += 1;
	}
	if (posibleMovimientoInverso(tablero, fila, col, DERECHA)) {
		tMovimiento movimiento;
		movimiento.direccion = DERECHA;
		movimiento.filaDestino = fila;
		movimiento.columnaDestino = col - 2;
		movimiento.filaSaltada = fila;
		movimiento.columnaSaltada = col - 1;
		posibles.movimientoArray[posibles.pos] = movimiento;
		posibles.pos += 1;
	}
	if (posibleMovimientoInverso(tablero, fila, col, IZQUIERDA)) {
		tMovimiento movimiento;
		movimiento.direccion = IZQUIERDA;
		movimiento.filaDestino = fila;
		movimiento.columnaDestino = col + 2;
		movimiento.filaSaltada = fila;
		movimiento.columnaSaltada = col + 1;
		posibles.movimientoArray[posibles.pos] = movimiento;
		posibles.pos += 1;
	}
	srand(time(NULL));
	int opcion = (0 + rand() % (posibles.pos- 0));
	bool hayOpcion = false;
	if (posibles.pos >= 1) {
		hayOpcion = true;
		mov = posibles.movimientoArray[opcion];
	}

	return hayOpcion;
}
bool posibleMovimientoInverso(const tTablero& tablero, int fila, int col, tDireccion dir) {
	bool posible = false;
	switch (dir) {
		case ARRIBA:
			if ((tablero.fila > (fila + 2)) &&
				(tablero.tCeldaArray[fila+2][col] == NULA) &&
				(tablero.tCeldaArray[fila+1][col] == NULA)
				) {
				posible = true;
			}
			break;
		case ABAJO:
			if ((0 <= (fila - 2)) &&
				(tablero.tCeldaArray[fila - 2][col] == NULA) &&
				(tablero.tCeldaArray[fila - 1][col] == NULA)
				) {
				posible = true;
			}
			break;
		case DERECHA:
			if (((col - 2) >= 0) &&
				(tablero.tCeldaArray[fila][col - 2] == NULA) &&
				(tablero.tCeldaArray[fila][col - 1] == NULA)
				) {
				posible = true;
			}
			break;
		case IZQUIERDA:
			if ((tablero.columna > (col + 2)) &&
				(tablero.tCeldaArray[fila][col + 2] == NULA) &&
				(tablero.tCeldaArray[fila][col + 1] == NULA)
				) {
				posible = true;
			}
			break;
	}

	return posible;
}
void realizaMovimientoInverso(tTablero& tablero, int fila, int col, const tMovimiento& mov) {
	tablero.tCeldaArray[fila][col] = VACIA;
	tablero.tCeldaArray[mov.filaSaltada][mov.columnaSaltada] = FICHA;
	tablero.tCeldaArray[mov.filaDestino][mov.columnaDestino] = FICHA;
}
