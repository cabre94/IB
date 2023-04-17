#include <iostream>
#include <cmath>
#include <iomanip>

#define EPS 1e-4

using namespace std;

double miSqrt_kk(double a){
	int i = 1;
	double x_i = 1, x_f = (1+a)/2;
	// El criterio de convergencia es que dos terminos continuos de la sucesion
	// sean iguales, de manera que la variacion termino a termino sea menor que
	// la precision de la maquina.
	while(x_f != x_i){
		x_i = x_f;
		x_f = ( x_i + a/x_i ) / 2;
		i += 1;
	}
	
	return x_f;
}

double miSqrt(double a){
	int i = 1;
	double x_i = 1, x_f = (1+a)/2;
	// El criterio de convergencia es que dos terminos continuos de la sucesion
	// tengan un diferencia menor que una cota dada
	while(abs(x_f - x_i) >= EPS ){
		x_i = x_f;
		x_f = ( x_i + a/x_i ) / 2;
		i += 1;
	}
	
	return x_f;
}

int main(){
	double a;
	cout << "Ingrese el numero para calcular su raiz cuadrada:\n";
	cin >> a;

	cout << "El valor obtenido a partir de la funcion sqrt() es: " << sqrt(a) << ".\n";	
	cout << "El valor obtenido a partir de la sucesion es: " << miSqrt(a) << ".\n";
	cout << "El valor obtenido a partir de la sucesion sin cota: " << miSqrt_kk(a) << ".\n";

	cout << setprecision(20) << "Cambiamos la precision del cout\n";
	cout << "El valor obtenido a partir de la funcion sqrt() es: " << sqrt(a) << ".\n";	
	cout << "El valor obtenido a partir de la sucesion es:       " << miSqrt(a) << ".\n";
	cout << "El valor obtenido a partir de la sucesion sin cota: " << miSqrt_kk(a) << ".\n";

	return 0;
}

// Con amor, Cabre.