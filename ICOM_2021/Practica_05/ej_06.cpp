#include <iostream>

using namespace std;

class A{
public:
	A(){cout << "Creando " << this << " con default constructor" << endl;}
	A(const A &a){cout << "Creo una copia de " << &a << " en " << this << endl;}
	~A(){cout << "Destruyo " << this << endl;}
};

void f(A &a){
	cout << "Dentro de f()" << endl;
}


int main(){

	A a1;

	f(a1);

	return 0;
}

// Con amor, Cabre.