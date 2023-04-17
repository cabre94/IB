#include <iostream>

using namespace std;

class A{
public:
	A(){cout << "Creando " << this << " con default constructor" << endl;}
	A(const A &a){cout << "Creo una copia de " << &a << " en " << this << endl;}
	~A(){cout << "Destruyo " << this << endl;}
};

void f(A a){
	cout << "En f() estamos usando " << &a << endl;
}

A g(){
	A a;
	cout << "En g()" << endl;
	return a;
}


int main(){

	A a1;

	// Aca se llama al copy constructor por crear un objeto a partir de otro
	cout << endl << "A a2 = a1;" << endl;
	A a2 = a1;

	// Aca llamamos a f(a1), que toma un A por valor (o sea, una copia).
	// Esa copia se crea con el copy constructor y es lo que usa f
	cout << endl << "f(a1);" << endl;
	cout << "Antes de f(a1)" << endl;
	f(a1);
	cout << "Despues de f(a1)" << endl;

	// Aca puede que no se este llamando al copy constructor como uno esperaria
	// del enunciado del ejercicio porque se esta haciendo una copy initialization
	// https://stackoverflow.com/questions/19019407/why-copy-constructor-is-not-called-here
	// En mi compilador, compilando con la opcion -fno-elide-constructors
	// usa el copy constructor.
	// Si usas el Code::Blocks, vas a tener que preguntar como hacerlo porque ni idea
	// O mejor, deja de usar esa verga y usa VSCode.   
	cout << endl << "A a3 = g();" << endl;
	cout << "Antes de g()" << endl;
	A a3 = g();
	cout << "Despues de g()" << endl << endl;

	return 0;
}

// Con amor, Cabre.