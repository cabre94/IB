#include <iostream>

using namespace std;

class A{
public:
	int elem;
	A(int e){
		elem = e;
		cout << "Creo A con A::A(int) " << this << endl;
	}
	~A(){cout << "Destruyo A " << this << endl;}
};


int main(){

	A a1(5);

	A a2 = a1;	// Aca nos creamos a2 copiandonos lo que tenga a1.

	cout << a2.elem << endl;

	return 0;
}

/*
Deberia mostrarte algo como esto

Creo A con A::A(int) 0x7ffc62a4e2e0
5
Destruyo A 0x7ffc62a4e2e4
Destruyo A 0x7ffc62a4e2e0

De donde verga sale el A creado en 0x7ffc62a4e2e4? Bueno, ese es el A que nos
copiamos cuando hicimos A a2 = a1;. Cuando creamos un objeto a partir de otro,
no se llaman a los constructores normales que toman argumentos, si no que se
llama al constructor copia.

Cuando nosotros no definimos un constructor copia, el compilador crea uno por
defecto, lo mismo que pasaba con el constructor en el ejercicio anterior si no
lo definiamos. Ese constructor copia por defecto lo que hace es copiar miembro
a miembro "a lo bruto". Muchas veces esto nos sirve y listo, mas adelante no.

Cuestion, al llamarse a ese constructor copia, se crea un objeto de una forma
diferente y por eso no se printea nada.

*/

// Con amor, Cabre.