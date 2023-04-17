#include <iostream>
#include <cmath>

using namespace std;

#define NUM_PASOS 10000
#define PASOS_INTERMEDIOS 10

// enumeración de las posibles direcciones (la última es auxiliar)
enum Direction {LEFT, RIGHT, UP, DOWN, LUP, RUP, LDOWN, RDOWN, NONE, NUM_DIRS};

struct Entity{	// Tipo definido por el usuario para representar a la entidad
	int x, y;	// representación: 2 enteros para representar la posicion.

	void move(Direction d){	
		switch(d){
			case LEFT:  x--; break;
			case RIGHT: x++; break;
			case UP:    y++; break;
			case DOWN:  y--; break;
			case LUP:	x--; y++; break;
			case RUP:	x++; y++; break;
			case LDOWN:	x--; y--; break;
			case RDOWN:	x++; y--; break;
			case NONE:  break;
			default: break; // si llega hasta aca debería disparar una excepcion
							// (que es algo que se ve mas adelante).
		}
	}

	// Metodo para calcular la distancia de el punto al origen.
	double Dist(){
		return sqrt(x*x + y*y);
	}

	// Metodo para printear la posicion x, y, la distancia.
	void print(){
		cout << "X: " << x << "\tY: " << y << "\tDist.: " << Dist() << endl;
  	}
};

double experimento(int N){
	Entity e = { 0, 0 };
	srand(time(0));

	for(int contador = 0; contador < N; contador++){
		e.move( Direction(rand() % NUM_DIRS) );  // entero ‘casteado’ a Direction
		// if(contador % PASOS_INTERMEDIOS == 0)
		// 	e.print();
	}
	// Printeo la posicion final
	// e.print();

	return e.Dist();
}

double experimentos(int M, int N){
	double prom = 0;
	for(int i=0; i < M; i++){
		prom += experimento(N);
	}
	return prom / M;
}


int main() {

	for(int M = 1; M < 1e8; M*=10){
		experimentos(100, 10000);
	}

	return 0;
}

// Con amor, Cabre.