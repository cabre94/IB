#include <iostream>
#include <set>
#include <ctime>
#include <chrono>
#include <unordered_set>
#include <vector>
#include <algorithm>

int main(){
	using namespace std::chrono;
	high_resolution_clock::time_point tic, tac;

	srand(time(0));

	std::vector<int> my_vec;
	std::set<int> my_set;
	std::unordered_set<int> my_uset;

	for(size_t i=0; i < 10000000; ++i)
		my_vec.push_back(rand() % 100000);
	size_t size = 10000;
	
	std::cout << "N\tSet-Ins\tuSet-Ins\tSet-find\tuSet-find" << std::endl;
	
	for(size_t N = 10; N < my_vec.size(); N*=10){
		std::cout << N << "\t";
		my_set.clear();
		my_uset.clear();
		// Agregamos N valores
		// Ya que estamos, medimos cuanto tarda cada uno
		tic = high_resolution_clock::now();
		my_set.insert(my_vec.begin(), my_vec.begin() + N);
		tac = high_resolution_clock::now();

		std::cout << duration_cast<microseconds>(tac-tic).count() << " ms\t";

		//unordered-set
		tic = high_resolution_clock::now();
		my_uset.insert(my_vec.begin(), my_vec.begin() + N);
		tac = high_resolution_clock::now();

		std::cout << duration_cast<microseconds>(tac-tic).count() << " ms\t";

		//	Mezclamos como para no buscar exactamente lo mismo que agregamos
		std::random_shuffle(my_vec.begin(), my_vec.end());

		// Set - Buscamos 10000 elementos y vemos cuanto tarda en promedio
		tic = high_resolution_clock::now();
		for(size_t i = 0; i < size; i++)
			my_set.find(my_vec[i]);
		tac = high_resolution_clock::now();
		std::cout << duration_cast<microseconds>(tac-tic).count()/(1.*size) << " ms\t";

		// Unordered set
		tic = high_resolution_clock::now();
		for(size_t i = 0; i < size; i++)
			my_uset.find(my_vec[i]);
		tac = high_resolution_clock::now();
		std::cout << duration_cast<microseconds>(tac-tic).count()/(1.*size) << " ms\n";

	}

	return 0;
}