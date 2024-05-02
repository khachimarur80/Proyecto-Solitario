#include "tablero.h"
#include "juego.h"
#include "movimiento.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <ctime>

using namespace std;

void jugar(tJuego juego, bool& repetir) {
	repetir = false;
	while (juego.estado == JUGANDO) {
		mostrar(juego.tablero);
		ejecutarMovimiento(juego);
	}
	if (juego.estado == GANADOR) {
		mostrar(juego.tablero);
		cout << "Enhorabuena! Quieres jugar otra partida ? S/N: ";
	}
	else if (juego.estado == BLOQUEO) {
		mostrar(juego.tablero);
		repetir = true;
		cout << "Vaya! Casi lo tenias! Quieres intentarlo otra vez? S/N: ";
	}
}

int main() {
	tJuego juego;
	bool seguirJugando = true;
	char aleatorio = 'S';
	bool repetir = false;
	do {
		if (repetir) {
			jugar(juego, repetir);
		}
		else {
			/*do {
				cout << "Quieres que el tablero se genere de forma aleatoria? S/N: ";
				cin >> aleatorio;
			}
			while (aleatorio != 'S' && aleatorio != 'N');*/

			if (aleatorio == 'S') {
				srand(time(NULL));
				int pasos = (MIN_PASOS + rand() % (MAX_PASOS + 1 - MIN_PASOS));
				generar(juego, pasos);
				jugar(juego, repetir);
			}
			else if (aleatorio == 'N') {
				if (cargar(juego, "tablero")) {
					jugar(juego, repetir);
				}
				else {
					cout << "Error al cargar tablero!" << endl;
					seguirJugando = false;
				}
			}
		}

		char respuesta;
		cin >> respuesta;
		while (respuesta != 'S' && respuesta != 'N') {
			cout << "Lo siento, no te entendí. Puedes repetirlo? S/N " << endl;
			cin >> respuesta;
		}
		if (respuesta == 'N') {
			cout << "Muchas gracias por jugar!" << endl;
			seguirJugando = false;
		}
	}
	while (seguirJugando);
	return 0;
}
