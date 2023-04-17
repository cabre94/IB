#include <iostream>

using namespace std;

struct Complejo{
    double re, im;
    void print(){
        cout << "(" << re << " + i " << im << ")\n";
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
		// Lo hago asi porque me da toc que se impriman signos extra o ceros
		// al pedo
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

	Complejo c1, c2, c3;

	cout << "Ingresar datos del primer complejo: " << endl;
	c1.ingresarValores();

	cout << "Ingresar datos del segundo complejo: " << endl;
	c2.ingresarValores();

	c3 = c1 + c2;
	cout << "c1 + c2 = ";
	c3.imprimir();

	c3 = c1 - c2;
	cout << "c1 - c2 = ";
	c3.imprimir();
	
	c3 = c1 * c2;
	cout << "c1 * c2 = ";
	c3.imprimir();

	c3 = c1 / c2;	
	cout << "c1 / c2 = ";
	c3.imprimir();

	return 0;
}

// Con amor, Cabre.