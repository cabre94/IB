/*
date: 19-10-21
File: 02_Caminata_sin_cruces.cpp
Author : Facundo Martin Cabrera
Email: cabre94@hotmail.com facundo.cabrera@ib.edu.ar
GitHub: https://github.com/cabre94
GitLab: https://gitlab.com/cabre94
Description:
*/

/*
Haciendo un histograma con bines de 500, nos da que todas las caminatas son
de un largo menor a 500. Esto es porque en cada movimiento hay 0.25 de chances
de volver a la posicion anterior. Despues de 500 pasos la probabilidad de no
haber vuelto atras en algun movimiento es (0.75)^500 = 3x10^-63.
*/

#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

#define MAX_PASOS 10000

// enumeración de las posibles direcciones (la última es auxiliar)
// Segun el enunciado, no podemos quedarnos quietos y las 4 direcciones
// son arriba, abajo, izquierda y derecha
enum Direction{
	LEFT, RIGHT, UP, DOWN, NUM_DIRS
};

struct Punto2D{
	int x, y;
};

// Tipo definido por el usuario para representar a la entidad
struct Entity{
	const int N;	// Tamaño de la red
	Punto2D pos;	// Posicion actual
	int num_pasos;
	vector<Punto2D> camino;
	bool cruce;
	
	Entity(int N_) : N{N_}, pos{N/2, N/2}, num_pasos{0}{
		camino.push_back(pos);
		cruce = false;
	}

	void move(Direction d){	
		// Nos movemos segun la direccion correspondiente
		switch(d){
			case LEFT:  pos.x--; break;
			case RIGHT: pos.x++; break;
			case UP:    pos.y++; break;
			case DOWN:  pos.y--; break;
		}
		// Mantenemos las posiciones dentro de la red de NxN
		pos.x = (pos.x + N) % N;
		pos.y = (pos.y + N) % N;
		// Chequeamos si hay un cruce
		check_cruce();
		// Agreagamos la posicion al camino recorrido
		camino.push_back(pos);
		// Aumentamos el numero de pasos
		num_pasos++;
	}
	
	// Metodo para printear la posicion x, y
	void print(){
		cout << "X: " << pos.x << "\tY: " << pos.y << endl;
	}
	
	// Chequeamos si hay un cruce, se puede hacer mas eficiente pero paja
	void check_cruce(){
		for(int i=0; i < camino.size(); ++i){
			if((pos.x == camino[i].x) && (pos.y == camino[i].y)){
				// cout << pos.x << "-" << pos.y << " | ";
				// cout << camino[i].x << "-" << camino[i].y << endl;
				cruce = true;
				break;
			}
		}
	}
};

// Funcion que realiza una caminata y retorna la cantidad de pasos
int experimento(int N){
	Entity e{N};

	while(e.num_pasos < MAX_PASOS && !e.cruce){
		e.move(UP);// entero ‘casteado’ a Direction
		// e.move(Direction(rand() % NUM_DIRS));// entero ‘casteado’ a Direction
	}

	return e.num_pasos;
}

// Funcion que corre una determinada cantidad de caminatas y hace un histograma
void histograma(int num_caminatas, int dim_red){
	int hist[20] = {0};
	vector<int> largos;

	// Generamos num_caminatas simulaciones
	for(int i=0; i < num_caminatas; i++)
		largos.push_back(experimento(dim_red));

	// Guardamos los largos en el histograma
	for(int i=0; i < num_caminatas; ++i)
		hist[largos[i] / (MAX_PASOS/20)]++;

	// Printeamos el histograma
	for(int i=0; i < 20; ++i)
		cout << hist[i] << endl;
}


int main() {
	srand(time(0));

	histograma(1000, 1000);

	return 0;
}

