#include <iostream>

using namespace std;

class A1{
public:
	int x;
};

// La misma clase que A1, pero con un constructor que toma un argumento.
class A2{
public:
	A2(int x_){x = x_;}
	int x;
};


int main(){

	A1 a1;

	// A2 a2;

	return 0;
}

/*
Si vos no definis NINGUN constructor, el compilador crea uno por defecto que
no toma argumentos.
Si vos definis algun constructor, el compilar no genera ninguno. Asi que la
unica forma de instanciar (crear) objetos es a partir de los constructores que
VOS definis. Es por eso que para crear un objeto A2, si o si le tenes que pasar
un entero como argumento, asi:
	A2 a2(42);
Podes definir mas de un constructor, por ejemplo:

class A3{
public:
	A3(){x = 0;}
	A3(int x_){x = x_;}
	int x;
};

Entonces vos podes crear A3ces de dos formas, una pasandole un entero, que es
lo que guarda en x, y otro que no le pasas nada y guarda un 0.
	A3 a3(3); -> guarda un 3
	A3 otro_a3; -> guarda un 0
*/

// Con amor, Cabre.