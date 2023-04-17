#include "misfuncs.h"
#include <ctime>
#include <ratio>
#include <chrono>
#include <algorithm>


int main(){
	srand(time(0));

	cout << "Para arrays nativos:" << endl;
	cout << "Tamaño\tTiempo [ms]\n";

	for(int i=1; i <= 1e5; i = i*10){
		double arr[i];

		// Inicializo con numeros entre 0 y 1000
		for(int j=0; j < i; j++){
			arr[j] = rand() % 1000;
		}

		// Tomo el tiempo inicial
		time_t tic = time(0);
		// Ordeno
		OrdenaArrayNativo(arr,i);
		// Tomo el tiempo final
		time_t tac = time(0);

		time_t time_span = tac - tic;

		cout.precision(2);
		cout << i << '\t' << time_span << endl;
	}

	cout << "Para vectors de <vector>:" << endl;
	cout << "Tamaño\tTiempo [ms]\n";

	for(int i=1; i <= 1e5; i = i*10){
		vector<double> vec(i, 0);

		// Iniciliazo con numeros entre 0 y 1000
		for(int j=0; j < i; j++){
			vec[j] = rand() % 1000;
		}

		// Tomo el tiempo inicial
		time_t tic = time(0);
		// Ordeno
		sort(vec.begin(), vec.end());
		// Tomo el tiempo final
		time_t tac = time(0);

		time_t time_span = tac - tic;

		cout.precision(2);
		cout << i << '\t' << time_span << endl;
	}
	
	return 0;
}

// Con amor, Cabre.