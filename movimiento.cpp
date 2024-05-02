#include "movimiento.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <ctime>

using namespace std;

bool fichaBloqueada(const tTablero& tablero, int fila, int col) {
	bool bloqueada = false;

	if (tablero.tCeldaArray[fila][col]==FICHA) {

		tMovimiento mov;
		tMovimientoLista posibles;
		int i = 0;

		for (tDireccion dir = ARRIBA; dir <= IZQUIERDA; dir = tDireccion(dir + 1)) {
			mov =  moviendo(dir, fila, col);
			posibles.movimientoArray[i] = mov;
			i += 1;
		}
		posibles.pos = 4;

		bloqueada = !movimientosPosibles(tablero, fila, col, posibles);
	}

	return bloqueada;
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
		tMovimiento mov;

		for (tDireccion dir = ARRIBA; dir <= IZQUIERDA; dir = tDireccion(dir + 1)) {
			mov = moviendo(dir, fila, col);
			if (
				((0 <= mov.filaDestino) && (mov.filaDestino < tablero.fila)) &&
				((0 <= mov.columnaDestino) && (mov.columnaDestino < tablero.columna)) &&
				esNula(tablero, mov.filaSaltada, mov.columnaSaltada) &&
				esNula(tablero, mov.filaDestino, mov.columnaDestino)
				) {
				listaMov.movimientoArray[listaMov.pos] = mov;
				listaMov.pos += 1;
				alguno = true;
			}
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
	srand(time(NULL));
	bool hayOpcion = false;
	if (movimientosPosibles(tablero, fila, col, posibles)) {
		int opcion = (0 + rand() % (posibles.pos- 0));
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
