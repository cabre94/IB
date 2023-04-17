#include <iostream>

using namespace std;

double calculaE(){
	double x_i = 1, x_f = 2;	// Taylor a orden 0 y orden 1 en x=1 para e^x
	int i = 1;					// Orden del Taylor
	double n = 1;				// Variable para tener el factorial que va a
								// ir en el denominador
	// En definitiva el Taylor de e^x en x=1 es la suma de los terminos 1/(n!)
	// que es lo que hace este while. El criterio para pararlo es cuando los
	// terminos que sumamos son tan pedorros que la sumatoria de mantiene cte.
	while(x_f != x_i){
		i++;
		n *= i;
		x_i = x_f;
		x_f += 1.0/n;
	}
	return x_f;
}

int main(){
	// Esto es para setear la cantidad de cifras que da el cout
	cout.precision(20);	

	cout << "e = " << calculaE() << endl;
	
	return 0;
}

// Con amor, Cabre.