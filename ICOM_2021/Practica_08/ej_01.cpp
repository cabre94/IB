#include <iostream>

using namespace std;

class Punto2D{
	double x, y;
public:
	void initialize(){
		cout << "Ingresar coordenada x: " << endl;
		cin >> x;
		cout << "Ingresar coordenada y: " << endl;
		cin >> y;
	}
};

class Complejo{
private:
    double re, im;

public:
    Complejo(){}
    Complejo(double re_, double im_){re = re_; im = im_;}
    void print(){
        cout << "(" <<re << " + i " << im << ")\n";
    }
    Complejo operator+(Complejo a) {
        Complejo result = {re + a.re, im + a.im};
        return result;
    }
	Complejo operator-(Complejo a) {
        Complejo result = {re - a.re, im - a.im};
        return result;
    }
	Complejo operator*(Complejo a){
		Complejo result = {re*a.re - im*a.im, re*a.im + im*a.re};
		return result;
	}
	Complejo operator/(Complejo a){
		Complejo result = {(re*a.re + im*a.im) / (a.re*a.re + a.im*a.im),
						(im*a.re - re*a.im) / (a.re*a.re + a.im*a.im)};
		return result;
	}
	void ingresarValores(){
		cout << "Ingresar la parte real: ";
		cin >> re;
		cout << "Ingresar la parte imaginaria: ";
		cin >> im;
	}
	void imprimir(){
		if(re == 0 && im ==0)
			cout << 0;
		else if(re != 0)
			cout << re;

		if(im == 1 && re == 0)
			cout << "i";
		else if(im == 1)
			cout << "+i";
		else if(im == -1)
			cout << "-i";
		else if(im > 0)
			cout << "+i" << im;
		else if(im < 0)
			cout << "-i" << -1*im;
		
		cout << endl;
	}
	
};



int main(){
	// Inicializo las arrays de dos componentes para cada tipo de dato
	char c[] = "ab";
	int i[2];
	float f[2];
	double d[2];
	Complejo complejo[2];
	Punto2D punto[2];

	// Imprimo la direccion de memoria de cada componente de cada variable
	cout << "Posicion de las variables char:    " << (void *)&c[0] << '\t' << (void *)&c[1] << endl;
	cout << "Posicion de las variables int:     " << &i[0] << '\t' << &i[1] << endl;
	cout << "Posicion de las variables float:   " << &f[0] << '\t' << &f[1] << endl;
	cout << "Posicion de las variables double:  " << &d[0] << '\t' << &d[1] << endl;
	cout << "Posicion de las variables Complex: " << &complejo[0] << '\t' << &complejo[1] << endl;
	cout << "Posicion de las variables Punto3D: " << &punto[0] << '\t' << &punto[1] << endl << endl;

	// Ahora imprimo la diferencia entre las variables
	cout << "Diferencia de las variables char:    " << (intptr_t)&c[1]-(intptr_t)&c[0] << endl;
	// cout << "Diferencia de las variables int:     " << (ptrdiff_t) (&i[1]-&i[0]) << endl;
	cout << "Diferencia de las variables int:     " << (intptr_t)&i[1]-(intptr_t)&i[0] << endl;
	cout << "Diferencia de las variables float:   " << (intptr_t)&f[1]-(intptr_t)&f[0] << endl;
	cout << "Diferencia de las variables double:  " << (intptr_t)&d[1]-(intptr_t)&d[0] << endl;
	cout << "Diferencia de las variables Complex: " << (intptr_t)&complejo[1]-(intptr_t)&complejo[0] << endl;
	cout << "Diferencia de las variables Punto3D: " << (intptr_t)&punto[1]-(intptr_t)&punto[0] << endl << endl;

	// Por ultimo, imprimo el tamaño de cada variable
	cout << "Tamaño de la variable char:    " << sizeof(c[0]) << endl;
	cout << "Tamaño de la variable int:     " << sizeof(i[0]) << endl;
	cout << "Tamaño de la variable float:   " << sizeof(f[0]) << endl;
	cout << "Tamaño de la variable double:  " << sizeof(d[0]) << endl;
	cout << "Tamaño de la variable Complex: " << sizeof(complejo[0]) << endl;
	cout << "Tamaño de la variable Punto3D: " << sizeof(punto[0]) << endl;

	return 0;
}

/*
La diferencia entre las direcciones de memoria de elementos contiguos es igual
al sizeof de cada tipo de dato. Esto es porque los arreglos se almacenan en memoria
de manera contigua.

Para los punteros a char, hace falta "castearlo" a void*, porque el operador
<< de cout funciona de forma distinta para los char*. Los char* se usan como
cadenas de caracteres y lo esperable en ese caso es que te imprima todos los
caracteres hasta que termine el arreglo con el 0.
*/

// Con amor, Cabre.