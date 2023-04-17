#include "misfuncs.h"
#include <ctime>
#include <ratio>
#include <chrono>
#include <algorithm>

using namespace std::chrono;

int main(){
	srand(time(0));

	cout << "Para arrays nativos:" << endl;
	cout << "Tamaño\tTiempo [ms]\n";

	for(int i=1; i <= 1e5; i = i*10){
		double kk[i];

		// Inicializo con numeros entre 0 y 1000
		for(int j=0; j < i; j++){
			kk[j] = rand() % 1000;
		}

		// Tomo el tiempo inicial
		high_resolution_clock::time_point Tic = high_resolution_clock::now();
		OrdenaArrayNativo(kk,i);	// Ordeno
		// Tomo el tiempo final
		high_resolution_clock::time_point Tac = high_resolution_clock::now();

		duration<double, std::milli> time_span = Tac - Tic;

		//cout.precision(2);
		cout << i << '\t' << time_span.count() << endl;
	}

	cout << "Para arrays de <array>:" << endl;
	cout << "Tamaño\tTiempo [ms]\n";

	for(int i=1; i <= 1e5; i = i*10){
		vector<double> vec(i, 0);

		// Iniciliazo con numeros entre 0 y 1000
		for(int j=0; j < i; j++){
			vec[j] = rand() % 1000;
		}

		// Tomo el tiempo inicial
		high_resolution_clock::time_point Tic = high_resolution_clock::now();
		std::sort(vec.begin(), vec.end());	// Ordeno
		// Tomo el tiempo final
		high_resolution_clock::time_point Tac = high_resolution_clock::now();

		duration<double, std::milli> time_span = Tac - Tic;

		//cout.precision(2);
		cout << i << '\t' << time_span.count() << endl;
	}
	
	return 0;
}

// Con amor, Cabre.