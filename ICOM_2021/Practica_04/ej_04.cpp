#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

#define SIZE 20

// Ordena array nativo de forma creciente
void OrdenaArrayNativo(int V[], int n);
// Imprime un array nativo
void ImprimeVector(int Vector[], int NumElementos);


int main(){
	srand(time(0));

	int arr[SIZE];
	for(int i=0; i<SIZE; i++){
		arr[i] = rand() % 100;
	}

	cout << "El array original es:" << endl;
	ImprimeVector(arr, SIZE);		// Imprimimos el array original
	OrdenaArrayNativo(arr, SIZE);	// Lo ordenamos

	cout << "El array ordenado de forma creciente es:" << endl;
	ImprimeVector(arr,SIZE);		// Lo imprimimos ordenado

	return 0;
}

// https://en.wikipedia.org/wiki/Bubble_sort
// https://es.wikipedia.org/wiki/Ordenamiento_de_burbuja
// En general este es el algoritmo mas facilongo para ordenar un array,
// pero es poco eficiente (no importa eso aca igual). 
void OrdenaArrayNativo(int V[], int n){
	int aux;

	for(int i=1; i < n; i++){
		for(int j=0; j < n-i; j++){
			if(V[j] > V[j+1]){
				aux = V[j];
				V[j] = V[j+1];
				V[j+1] = aux; 
			}
		}
	}

	return;
}

void ImprimeVector(int Vector[], int NumElementos){
	if(NumElementos <= 0)
		return;

	for(int i=0; i < NumElementos-1; i++)
		cout << Vector[i] << ' ';
	cout << Vector[NumElementos-1] << endl;
}

// Con amor, Cabre.