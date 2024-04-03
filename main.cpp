#include "tablero.h"
#include "juego.h"
#include "movimiento.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <ctime>

using namespace std;

void jugar(tJuego juego) {
	while (juego.estado == JUGANDO) {
		mostrar(juego.tablero);
		ejecutarMovimiento(juego);
	}
	if (juego.estado == GANADOR) {
		cout << "Enhorabuena! Quieres jugar otra partida ? S/N " << endl;
	}
	else if (juego.estado == BLOQUEO) {
		cout << "Vaya! Casi lo tenías! Quieres intentarlo otra vez? S/N " << endl;
	}
}

int main() {
	tJuego juego;
	bool seguirJugando = true;
	int ronda = 0;
	do {
		if (ronda == -1) {
			if (cargar(juego, "tablero")) {
				jugar(juego);
			}
			else {
				cout << "Error al cargar tablero!" << endl;
				seguirJugando = false;
			}
		}
		else {
			srand(time(NULL));
			int pasos = (MIN_PASOS + rand() % (MAX_PASOS + 1 - MIN_PASOS));
			generar(juego, pasos);
			jugar(juego);
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
		else {
			ronda += 1;
		}
	}
	while (seguirJugando);
	return 0;
}
