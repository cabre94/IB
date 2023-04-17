#include <iostream>

using namespace std;

// Se puede solo declarar la funcion (declarar es decir como se llama, que tipo
// de dato retorna y que tipo de datos toma como argumento) y declararla despues.
// Muchas veces es por claridad, pero otras es necesario hacerlo asi.
void ImprimeVector(double Vector[], int NumElementos);

int main(){
	srand(time(0));

	double vec[10];
	for(int i=0; i<10; i++){	// Inicializo el array con valores aleatorios
		vec[i] = rand() % 100;
	}

	ImprimeVector(vec,10);

	return 0;
}

void ImprimeVector(double Vector[], int NumElementos){
	if(NumElementos <= 0)
		return;

	cout << '{';
	for(int i=0; i < NumElementos-1; i++)
		cout << Vector[i] << ", ";
	cout << Vector[NumElementos-1] << '}' << endl;
}

// Con amor, Cabre.