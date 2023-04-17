#include <iostream>

#define MX 20
#define MY 20

using namespace std;

void FloodFill(int M[MX][MY], int X, int Y, int C1);
void imprimeMatriz(int M[MX][MY]);

int main(){
	int M[MX][MY] ={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0},
					{0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
					{0,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
					{0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
					{0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
					{0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
					{0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0},
					{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0},
					{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0},
					{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0},
					{0,0,0,0,0,1,0,0,0,0,0,1,1,1,0,0,0,1,0,0},
					{0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0},
					{0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0},
					{0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

	// Si, escribi la matriz de 20x20 del enunciado
	imprimeMatriz(M);

	cout << endl << "Ahora lo rellenamos" << endl << endl;
	FloodFill(M,9,9,1);

	imprimeMatriz(M);

	return 0;
}

// El caso base: cuando la celda a la que ya nos movimos esta pintada, no
// hacemos nada. Fijate que como la funcion retorna void, para cortar la
// recursion tenes que meter un return sin nada, si no la funcion sigue.
// La recursion: pinta arriba, pinta abajo, pinta a la izquierda y pinta a la
// derecha.
// Uno podria tener otro caso base, que es cuando X e Y estan afuera de la
// matriz (o sea, X < 0 o X >= MX o Y < 0 o Y >= MY), pero el enunciado dice
// que la curva es cerrada y el punto inicial esta adentro, asi que si nos 
// ponemos estrictos, no hace falta.
void FloodFill(int M[MX][MY], int X, int Y, int C1){
	if(M[X][Y] == C1)
		return;
	else{
		M[X][Y] = C1;
		FloodFill(M, X, Y+1, C1);
		FloodFill(M, X+1, Y, C1);
		FloodFill(M, X, Y-1, C1);
		FloodFill(M, X-1, Y, C1);
	}
}

void imprimeMatriz(int M[MX][MY]){
	for(int i=0; i < MX; i++){
		for(int j=0; j < MY; j++){
			if(M[i][j] == 0)
				cout << '-';
			else
				cout << 'o';
		}
		cout << endl;
	}
}

// Con amor, Cabre.