#include <iostream>

using namespace std;

class A{
public:
	A(){cout << "Creando A en " << this << " con default constructor" << endl;}
	A(const A &a){cout << "Creo una copia de A de " << &a << " en " << this << endl;}
	~A(){cout << "Destruyo A en " << this << endl;}
};

class B{
public:
	A a;
	B(){cout << "Creando B en " << this << " con default constructor" << endl;}
	~B(){cout << "Destruyo B en" << this << endl;}
};


int main(){

	B b1;

	cout << endl << "Copiamos b1 en b2" << endl;
	B b2 = b1;

	cout << endl << "Termina el main" << endl;

	return 0;
}

/*
El enunciado ya spoilea lo que hay que ver en el ejercicio. Si bien no creamos
un copy constructor para B, el copy constructor por defecto del compilador
llama a los definidos para los objetos contenidos. O sea, que no este definido
para B no quiere decir que no se use el definido para A. 
*/

// Con amor, Cabre.