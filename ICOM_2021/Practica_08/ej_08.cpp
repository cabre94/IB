#include <iostream>
#include <cmath>

using namespace std;

using fun_ptr_t = double (*)(double);
// la linea con el using se usa para no tener que hacer 
// double integra(double x0, double x1, double(*fun)(double));
// Basicamente define un tipo de variable que es un puntero a funciones que
// reciben double y devuelven double.

double integra(double a, double b, fun_ptr_t fun){
	double res = (b-a)*0.5*(fun(a)+fun(b)); // Calculo el primer valor, correspondiente a no dividir el intervalo en segmentos
											// (seria n=1 y, por lo tanto, h = b-a)
											// La idea es usar esta variable para ir comparando hasta que el resultado converja
	long n = 2; 							// Arrancamos dividiendo el intervalo en 2 segmentos.
	int cont = 0; 		// con esta variable vamos a contar cuantas veces seguidas el resultado coincidio con el anterior. La idea es que cuando
						// coincida 5 veces seguidas (cont = 5) entonces vamos a decir que el resultado ya converge.
	while(cont < 5){
		double aux = fun(a)+fun(b); 	// Calculo el primer y ultimo termino aparte, porque son los unicos que no tienen un *2
		double h = (double) (b-a)/n;	// Calculo el ancho h de los intervalos

		for(int j=1; j < n; j++)
			aux += 2*fun(a+j*h);
		aux = h*0.5*aux;

		if(fabs(res - aux) < 1e-6)	// Comparo con el resultado de la iteracion previa, la cota es arbitraria
			cont++;					// Si da menor que un cota (arbitraria), sumo uno al contador
		else
			cont = 0;						// Si no la reseteo

		res = aux;	// Piso el resultado previo de la integral
		n*=2;	// Duplico la cantidad de intervalos para la siguiente iteracion
	}

	return res;
}

int main(){

	cout << "La integral de cos entre 0 y PI es: " << integra(0,M_PI,cos) << endl;
	cout << "La integral de sin entre 0 y PI es: " << integra(0,M_PI,sin) << endl;

	return 0;
}

// Con amor, Cabre.