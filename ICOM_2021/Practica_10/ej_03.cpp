#include <iostream>
#include <vector>

using namespace std;

class Figura{
public:
	Figura(){cout << "Constructor Figura\t" << this << endl;}
	virtual void Dibujar(){cout << "Dibujo una Figura... ponele." << endl;}
	virtual ~Figura(){cout << "Destructor Figura\t" << this << endl;}
};

class Cuadrado : public Figura{
public:
	Cuadrado(){cout << "Constructor Cuadrado\t" << this << endl;}
	void Dibujar(){cout << "Dibujo un cuadrado: ■" << endl;}
	~Cuadrado(){cout << "Destructor Cuadrado\t" << this << endl;}
};

class Circulo : public Figura{
public:
	Circulo(){cout << "Constructor Circulo\t" << this << endl;}
	void Dibujar(){cout << "Dibujo un circulo: o" << endl;}
	~Circulo(){cout << "Destructor Circulo\t" << this << endl;}
};

class Triangulo : public Figura{
public:
	Triangulo(){cout << "Constructor Triangulo\t" << this << endl;}
	void Dibujar(){cout << "Dibujo un triangulo: △" << endl;}
	~Triangulo(){cout << "Destructor Triangulo\t" << this << endl;}
};

int main(){
	vector<Figura *> fig(4);

	fig[0] = new Figura;
	fig[1] = new Cuadrado;
	fig[2] = new Circulo;
	fig[3] = new Triangulo;

	cout << endl;
	for(int i=0; i < 4; i++)
		fig[i]->Dibujar();
	
	cout << endl;
	for(int i=0; i < 4; i++)
		delete fig[i];

	return 0;
}

/*
https://www.geeksforgeeks.org/virtual-destructor/
*/

// Con amor, Cabre.