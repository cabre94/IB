#include <iostream>

using namespace std;

// Funcion que calcula la cantidad de formas de llenar con dominos un rectangulo de 2xn casilleros
// Casos bases:
// Si n=1, solo podes poner una ficha vertical, asi que la cantidad de formas de
// llenar el tablero es 1.
// Si n=2, podes poner 2 verticales o dos horizontales, asi que la cantidad
// de formas de llenar el tablero es 1. 
// La recursion es para n > 2. Hay dos situaciones que deberias darte cuenta,
// centrate solo en como vas a poner las fichas la derecha (o izq, lo que se te
// cante). Las dos opciones son poner una vertical o dos horizontales.
// Si pones una vertical, tenes que ver cuantas formas tenes de ocupar para n-1
// Si pones dos horizon, tenes que ver cuantas formas tenes de ocupar para n-2
// La suma de esas dos, es la cantidad total de formas que tenes para n.
// Dibujalo hasta que quede claro.
int domino(int n){
	if(n == 1)
		return 1;
	else if(n == 2)
		return 2;
	else
		return domino(n-1) + domino(n-2);
}

int main(){
	int n;

	cout << "Ingrese el largo del tablero de 2xn:" << endl;
	cin >> n;

	cout << "La cantidad de formas de ordenar las fichas de domino en el";
	cout << " tablero de 2x" << n << " es " << domino(n) << endl;

	return 0;
}

// Con amor, Cabre.