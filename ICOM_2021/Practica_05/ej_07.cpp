#include <iostream>
#include <vector>

using namespace	std;

class A{
public:
	A(){cout << "Creando " << this << " con default constructor" << endl;}
	A(const A &a){cout << "Creo una copia de " << &a << " en " << this << endl;}
	~A(){cout << "Destruyo " << this << endl;}
};

int main(){

	A a;
	vector<A> v;

	// El std::vector tiene la particularidad de que todos sus elementos tienen
	// que estar contiguos en memoria. Entonces, al ir agregando elementos, 
	// puede ser necesario mover todos los elementos actuales a un nuevo espacio
	// de memoria, para que todos los elementos (nuevos con viejos) queden
	// contiguos en memoria.
	// Fijate que este reallocamiento solo es necesario cuando el tamaño es
	// potencia de 2. whaaaaaaaat. Igual esto creo que depende de la implementacion.
	cout << endl << "Agregamos 16 elementos" << endl;
	for(int i=0; i < 16; i++){
		cout << i << endl;
		v.push_back(a);
	}

	// Aca con el resize solo deberia verse el destructor 
	cout << endl << "Resize a 3 elementos" << endl;
	v.resize(3);

	// Dependiendo del tamaño del resize, puede ser que tambien se realloque
	// el contenido que ya estaba en el vector. Probar con distintos tamaños
	cout << endl << "Resize a 17 elementos" << endl;
	v.resize(17);

	cout << endl << "Fin del main" << endl;

	return 0;
}

// Con amor, Cabre.