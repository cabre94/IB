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

// Tambien podemos usar una funcion
void myfunction(int& x){
	x = 2*x;
}

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

	// Volvemos a duplicar los elementos pero usando la funcion
	std::for_each(myvector.begin(), myvector.end(), myfunction);

	std::cout << "myvector contains: ";
	for (auto it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << *it <<  ' ';
	std::cout << std::endl;


	return 0;
}