#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <algorithm>

// Podemos usar un functor
struct doubler{
    void operator()(int& x){
		x = 2*x;
	} // by reference!
};

// Un ejemplito que me gusto
struct DivisibleBy{
	const int d;
	DivisibleBy(int d_) : d(d_) {}
	bool operator()(int n) const {return n % d == 0;}
};

// struct isEven{
// 	bool operator()(int n) const {return n % 2 == 0;}
// };

int main(){
	srand(time(0));

	std::vector<int> myvector;

	for(int i=0; i < 10; ++i)
		myvector.push_back(i);
	
	std::cout << "myvector contains: ";
	for (auto it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << *it <<  ' ';
	std::cout << std::endl;

	// Duplicamos los elementos usando el functor
	std::for_each(myvector.begin(), myvector.end(), doubler{});

	std::cout << "myvector contains: ";
	for (auto it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << *it <<  ' ';
	std::cout << std::endl;
	
	// Chequeemos que todos son pares
	// Una for es hacerlo con [](int i){ return i % 2 == 0; }, que es una
	// funcion lambda. Para mi es horrible y creo que no lo vimos
	if(std::all_of(myvector.begin(), myvector.end(), [](int i){return i % 2 == 0;}))
		std::cout << "Todos son pares" << std::endl;
	else
		std::cout << "Algo dio mal" << std::endl;
	
	// Ahora hagamoslo con el functor que es mas agradable y entendible
	if(std::all_of(myvector.begin(), myvector.end(), DivisibleBy(2)))
		std::cout << "Todos son pares" << std::endl;
	else
		std::cout << "Algo dio mal" << std::endl;


	return 0;
}