#include <iostream>

template<class T>
T fibonacci_v1(){
	static T f1 = 0;
	static T f2 = 1;

	T aux = f1 + f2;
	f1 = f2;
	f2 = aux;

	return f1;
}

// template<class T>
// T fibonacci_v2(){

// }

int main(){

	for(int i=1; i <= 100; i++)
		std::cout << "Termino " << i << "-esimo: " << fibonacci_v1<int>() << std::endl;

	for(int i=1; i <= 100; i++)
		std::cout << "Termino " << i << "-esimo: " << fibonacci_v1<unsigned long>() << std::endl;
		// std::cout << "Termino " << j << "-esimo: " << fibonacci_v1<double>() << " " << typeid(fibonacci_v1<double>()).name() << std::endl;

	return 0;
}