#include <iostream>

using namespace std;

class A{
public:
	A(){cout << "Creo A " << this << endl;}
	~A(){cout << "Destruyo A " << this << endl;}
};

class B{
private:
	A a;
	// A a2;
public:
	B(){cout << "Creo B " << this << endl;}
	~B(){cout << "Destruyo B " << this << endl;}
};

int main(){

	B b[3];

	return 0;
}

/*
El orden de la destruccion es inverso al orden de la construccion.
*/

// Con amor, Cabre.