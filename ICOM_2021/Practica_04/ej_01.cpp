#include <iostream>
#include <array>
#include <vector>
#include <cassert>

using namespace std;

#define N 10	// Seria la cantidad de bines del histograma
#define TIRADAS 1000000

int main(){
	srand(time(NULL));

	// Inicializo el array nativo con ceros
	int hist[N] = {0}, index;

	// Inicializo el array con ceros
	array<int, N> hist_array {0};

	// Inicializo el vector con ceros
	vector<int> hist_vector {0};
	hist_vector.resize(N);

	// Genero los numeros aleatorios y obtengo a que indice (que seria a que
	// bin) corresponde sumarle uno al contador
	for(int i=0; i < TIRADAS; i++){
		index = rand() / (RAND_MAX / N);
		hist[index]++;
		hist_array[index]++;
		hist_vector[index]++;
	}

	// Un for como para chequear que las distintas implementaciones dan los
	// mismos histogramas, podria usar un assert
	for(int i=0; i < N; i++){
		assert((hist[i] == hist_array[i]) && (hist[i] == hist_vector[i]));
	}

	int suma = 0;

	for(int i=0; i<N; i++){
		cout << "Index " << i << ": " << hist[i]  << endl;
		suma += hist[i];
	}

	cout << suma << endl;

	return 0;
}

// Con amor, Cabre.