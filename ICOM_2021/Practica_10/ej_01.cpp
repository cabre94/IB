#include <iostream>

using namespace std;

class Figura{
public:
	virtual void Dibujar(){
		cout << "Dibujo una Figura... ponele." << endl;
	}
};

class Cuadrado : public Figura{
public:
	void Dibujar(){cout << "Dibujo un cuadrado: ■" << endl;}
};

class Circulo : public Figura{
public:
	void Dibujar(){cout << "Dibujo un circulo: o" << endl;}
};

class Triangulo : public Figura{
public:
	void Dibujar(){cout << "Dibujo un triangulo: △" << endl;}
};

int main(){
	Figura* fig[4];
	fig[0] = new Figura;
	fig[1] = new Cuadrado;
	fig[2] = new Circulo;
	fig[3] = new Triangulo;
	
	// Podemos usar el metodo Dibujar olvidandonos de que tipo de Figura es
	for(int i=0; i < 4; i++)
		fig[i]->Dibujar();
	
	// No hay que olvidar liberar la memoria
	for(int i=0; i < 4; i++)
		delete fig[i];

	return 0;
}

// Con amor, Cabre.