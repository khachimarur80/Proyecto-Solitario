#ifndef tablero.h
#define tablero.h

const int FILS = 6;
const int COLS = 6;
enum tCelda { NULA, VACIA, FICHA };
typedef tCelda tCeldaArray[FILS][COLS];
typedef struct {
	tCelda tCeldaArray[FILS][COLS];
	int fila;
	int col;
	int fMeta;
	int cMeta;
}tTablero;





void cargar(tTablero& tablero, ifstream& file);
bool valida(const tTablero& tablero, int fila, int col);
bool eleccionValida(const tTablero& tablero, int fila, int
	col);
void ponCelda(const tTablero& tablero, int fila, int col,
	tcelda celda);
	 bool esFicha(const tTablero& tablero, int fila, int col);
 bool esVacia(const tTablero& tablero, int fila, int col);
 void mostrar(const tTablero& tablero);


#endif
