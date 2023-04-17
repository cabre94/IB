#include <iostream>

using namespace std;

void InvierteArrayNativo(int V[], int n);
void ImprimeVector(int Vector[], int NumElementos);

int main(){
	int arr1[5] = {1, 2, 3, 4, 5};
	int arr2[4] = {1, 2, 3, 4};

	InvierteArrayNativo(arr1,5);
	InvierteArrayNativo(arr2,4);

	ImprimeVector(arr1,5);
	ImprimeVector(arr2,4);

	return 0;
}

void InvierteArrayNativo(int V[], int n){
	int aux;
	// Solo hace falta recorrer la mitad del array para invertirlo
	for(int i=0; i < (n/2); i++){
		aux = V[i];
		V[i] = V[n-1-i];
		V[n-1-i] = aux;
	}
}

void ImprimeVector(int Vector[], int NumElementos){
	if( NumElementos <= 0)
		return;
	
	for(int i=0; i < NumElementos-1; i++)
		cout << Vector[i] << ' ';
	cout << Vector[NumElementos-1] << endl;
}

// Con amor, Cabre.