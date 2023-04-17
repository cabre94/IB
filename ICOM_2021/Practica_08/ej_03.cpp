#include <iostream>
#include <ctime>

using namespace std;


// Funcion que transpone una matriz
void TransponeNN(double *matriz, int n);
// Funcion que imprime una matriz
void imprimeMatriz(double *matriz, int n);
// Funcion que genera una matriz de enteros al azar entre 0 y 1
void generaMatriz(double *matriz, int n);

int main(){
	srand(time(0));

	int n = 4;
	// double m[n*n];
	double m[n][n];
	generaMatriz(&m[0][0],n);
	imprimeMatriz(&m[0][0],n);

	// Ahora transponemos la matriz
	cout << endl;
	TransponeNN(&m[0][0], n);
	imprimeMatriz(&m[0][0], n);

	return 0;
}

void TransponeNN(double *matriz, int n){
	double aux;
	// No hay que recorrer toda la matriz, solo la triangular sup/inf sin la
	// diagonal
	for(int i=0; i < n; i++){
		for(int j=0; j < i; j++){
			aux = matriz[i*n + j];
			matriz[i*n + j] = matriz[i + n*j];
			matriz[i + n*j] = aux;
		}
	}
}

void imprimeMatriz(double *matriz, int n){
	for(int i=0; i < n; i++){
		for(int j=0; j < n; j++){
			cout << matriz[i*n+j] << ' ';
		}
		cout << endl;
	}
}

void generaMatriz(double *matriz, int n){
	for(int i=0; i < n; i++){
		for(int j=0; j < n; j++){
			matriz[i*n + j] = rand() % 10;
		}
	}
}
