#include <iostream>

using namespace std;

/*
this es la direccion de memoria del objeto. Cada B (y cada A) tiene SU propio
this, por eso lo uso aca para mostrar que son objetos distintos.
*/

class A{
public:
	A(){cout << "Creo A " << this << endl;}
};

class B{
private:
	A a;
	// A a2;
public:
	B(){cout << "Creo B " << this << endl;}
};

int main(){

	B b[3];

	return 0;
}

/*
Cosas para que veas en este ejercicio (capaz se me pase alguna, consulta):
- El orden en que se crean las cosas. Si B tiene un A adentro, primero se crea
A y despues se crea B. O sea, mas general, primero se crean los datos miembros
y luego se crea el objeto.
- Fijate que la direccion de memoria de un objeto B es la misma que la de SU
miembro A, esto es porque la direccion de memoria de un objeto coincide con la
de su primer miembro. Proba poner un segundo miembro A dentro de B, la direccion
de memoria del segundo A ya no coincide.
*/

// Con amor, Cabre.