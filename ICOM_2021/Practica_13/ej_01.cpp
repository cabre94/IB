#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <ctime>
#include <chrono>
#include <algorithm>


void sort_containers(){
	std::cout << "N\tList\tDeque\tVector" << std::endl;

	std::list<int> lista;
	std::deque<int> cola;
	std::vector<int> vec;

	std::chrono::high_resolution_clock::time_point tic, tac;

	for (size_t N = 10; N <= 10000000; N*=10){
		std::cout << N << "\t";

		// Limpio los containers
		lista.clear();
		cola.clear();
		vec.clear();
		
		// Agrego N elementos a los containers
		for(size_t i=0; i < N; ++i){
			int x = rand();

			lista.push_back(x);
			cola.push_back(x);
			vec.push_back(x);
		}

		// Mido los tiempos para la lista
		tic = std::chrono::high_resolution_clock::now();
		lista.sort();
		tac = std::chrono::high_resolution_clock::now();

		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(tac-tic).count() << " ms\t";

		// Mido los tiempos para la cola
		tic = std::chrono::high_resolution_clock::now();
		std::sort(cola.begin(), cola.end());
		tac = std::chrono::high_resolution_clock::now();

		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(tac-tic).count() << " ms\t";

		// Mido los tiempos para la vector
		tic = std::chrono::high_resolution_clock::now();
		std::sort(vec.begin(), vec.end());
		tac = std::chrono::high_resolution_clock::now();

		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(tac-tic).count() << " ms\n";
	}
}


int main(){
	srand(time(0));

	sort_containers();

	return 0;
}