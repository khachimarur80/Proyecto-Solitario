#include "tablero.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>

using namespace std;

const string FG_BLACK = "\x1B[30m";
const string FG_BLUE = "\x1b[34m";
const string BG_BLACK = "\x1B[40m";
const string BG_BROWN = "\x1B[48;5;94m";
const string BG_ORANGE = "\x1B[48;2;204;102;0m";
const string Reset = "\x1b[0m";

const char Horizontal = char(196);
const char UpperLeft = char(218);
const char UpperCross = char(194);
const char UpperRight = char(191);
const char Vertical = char(179);
const char MidLeft = char(195);
const char MidCross = char(197);
const char MidRight = char(180);
const char LowerLeft = char(192);
const char LowerCross = char(193);
const char LowerRight = char(217);
const char Square = char(219);


const int f_meta = 2, c_meta = 1;
const int DEFAULT_COLOR = -1;
// funciones para pintar el tablero
void pintaCabecera() {
    {
        cout << setw(2) << "    ";
        cout << setw(5) << 1;
        for (int i = 2; i <= COLS; i++)
            cout << setw(7) << i;
        cout << endl;
    }
}
void pintaBordeHorizontal(char left, char cross, char right) {
    cout << "    ";
    cout << left;
    for (int i = 0; i < COLS - 1; i++) {
        cout << string(6, Horizontal) << cross;
    }
    cout << string(6, Horizontal) << right << endl;
}

void pintaBordeCelda(int fila, int filaMeta, int colMeta, const tCeldaArray m) {
    cout << "    ";
    for (int k = 0; k < COLS; k++) {
        cout << Vertical;
        if (filaMeta == fila && colMeta == k)
            cout << BG_ORANGE;
        else if (m[fila][k] == 0)
            cout << BG_BLACK;
        else
            cout << BG_BROWN;
        cout << "      ";
        cout << Reset;
    }
    cout << Vertical << endl;
}

void pintaCentroCelda(int fila, int filaMeta, int colMeta, const tCeldaArray m) {
    cout << "  " << setw(2) << fila + 1;
    for (int k = 0; k < COLS; k++) { // cada col
        cout << Vertical;
        if (m[fila][k] == 0) {
            cout << BG_BLACK;
            cout << "      ";
        }
        else {
            if (filaMeta == fila && colMeta == k)
                cout << BG_ORANGE;
            else
                cout << BG_BROWN;
            cout << "  ";
            if (m[fila][k] == 1)
                cout << FG_BLACK;
            else
                cout << FG_BLUE;
            cout << Square << Square;
            cout << Reset;
            if (filaMeta == fila && colMeta == k)
                cout << BG_ORANGE;
            else
                cout << BG_BROWN;
            cout << "  ";
        }
        cout << Reset;
    }
    cout << Vertical << endl;
}

// funciones que hacen update del tablero
void cargar(tTablero& table) {
    ifstream archivo;
    int aux;
    archivo.open("tablero.txt");
    if (archivo.is_open()) {
        archivo >> table.fila;
        archivo >> table.columna;
        archivo >> aux;
        for (int i = 0; i < table.fila; i++) {
            for (int j = 0; j < table.fila; j++) {
                if (aux == 0) {
                    table.tCeldaArray[i][j] = NULA;
                }
                else if (aux == 1) {
                    table.tCeldaArray[i][j] = VACIA;
                }
                else if (aux == 2) {
                    table.tCeldaArray[i][j] = FICHA;
                }
            }
        }
        archivo >> table.fMeta;
        archivo >> table.cMeta;
        archivo.close();
    }
    else {
        cout << "no se pudo abrir ";
    }
}
bool valida(const tTablero& table, int fila, int col)
{
    return true;
};

bool eleccionValida(const tTablero& table, int fila, int
    col)
{
    return true;
};
void ponCelda(const tTablero& table, int fila, int col,
    tCelda celda)
{};

bool esFicha(const tTablero& table, int fila, int col)
{
    return true;
};

bool esVacia(const tTablero& table, int fila, int col)
{
    return true;
};

void mostrar(const tTablero& table) {
    system("cls"); // borrar consola
    cout << Reset;
    pintaCabecera();
    pintaBordeHorizontal(UpperLeft, UpperCross, UpperRight);
    for (int fila = 0; fila < FILS; fila++) {
        pintaBordeCelda(fila, f_meta, c_meta, table.tCeldaArray);
        pintaCentroCelda(fila, f_meta, c_meta, table.tCeldaArray);
        pintaBordeCelda(fila, f_meta, c_meta, table.tCeldaArray);
        if (fila < FILS - 1) {
            pintaBordeHorizontal(MidLeft, MidCross, MidRight);
        }
        else {
            pintaBordeHorizontal(LowerLeft, LowerCross, LowerRight);
        }
    }
}











