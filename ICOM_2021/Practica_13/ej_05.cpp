#include <iostream>
#include <list>
#include <vector>

/*
// Una version template de la print_list
template<typename T>
void print_list(const std::list<T> &mylist){
	// El iterador tiene que ser const_iterator porque lo que le pasamos es una
	// lista constante.
	// hay que usar el typename porque es un template y entonces el tipo de
	// iterador depende del valor de T
	typename std::list<T>::const_iterator it;

	std::cout << "mylist contains: ";
	for (it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << *it <<  ' ';
	std::cout << std::endl;
}
*/

void print_list(const std::list<int> &mylist){
	// El iterador tiene que ser const_iterator porque lo que le pasamos es una
	// lista constante.
	std::list<int>::const_iterator it;

	std::cout << "mylist contains: ";
	for (it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << *it <<  ' ';
	std::cout << std::endl;
}

int main(){
	std::list<int> mylist;
	std::list<int>::iterator it;

	// set some initial values:
	for (int i = 1; i <= 5; ++i)
		mylist.push_back(i);
	print_list(mylist);		// 1 2 3 4 5

	it = mylist.begin();
	++it; // it points now to number 2

	// Agregamos un 10 ANTES de lo que apunta el it (o sea, el 2)
	mylist.insert(it, 10);
	print_list(mylist);		// 1 10 2 3 4 5

	// Agregamos dos 20 ANTES de lo que apunta el it
	// "it" still points to number 2           
	mylist.insert(it, 2, 20);
	print_list(mylist);		// 1 10 20 20 2 3 4 5

	--it; // it points now to the second 20 

	std::vector<int> myvector(2, 30);	// Vector con dos 30
	// Agregamos los elementos de myvector ANTES de lo que apunta el it
	// (el segundo 20)
	mylist.insert(it, myvector.begin(), myvector.end());
	// 1 10 20 30 30 20 2 3 4 5

	return 0;
}