#include "icom_helpers.h"

class Figura{
public:
	virtual void Dibujar(){
		cout << "Dibujo una Figura... ponele." << endl;
	}
};

class Cuadrado : public Figura{
public:
	void Dibujar(){
		cout << "Dibujo un cuadrado:" << endl;
		cout << "╔═══╗©" << endl;
		cout << "║   ║" << endl;
		cout << "╚═══╝" << endl;
		//cout << "Dibujo un cuadrado ■" << endl;
	}
};

class Circulo : public Figura{
public:
	void Dibujar(){
		cout << "Dibujo un circulo:" << endl;
		cout << "O" << endl;
	}
};

class Triangulo : public Figura{
public:
	void Dibujar(){
		cout << "Dibujo un triangulo:" << endl;
		cout << "△" << endl;
	}

};

int main(){
	Figura* fig[4];
	fig[0] = new Figura;
	fig[1] = new Cuadrado;
	fig[2] = new Circulo;
	fig[3] = new Triangulo;

	fig[0]->Dibujar();
	fig[1]->Dibujar();
	fig[2]->Dibujar();
	fig[3]->Dibujar();

	delete fig[0];	
	delete fig[1];	
	delete fig[2];	
	delete fig[3];	

	return 0;
}
// Con amor, Cabre.