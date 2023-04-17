#include <iostream>
#include <cmath>

using namespace std;

int main(){
	long int N, A = 0;
	srand(time(0));

	cout << "Ingrese el numero de iteraciones que desea realizar: \n";
	cin >> N;

	for(long int i=0; i<N; i++){
		// Una variable aleatoria para representar la altura de un extremo
		double y   = (double) rand() / RAND_MAX;
		// Otra para el angulo de inclinacion de la aguja
		double theta = (double) rand();
		
		// Saco el cateto vertical del triangulito rectangulo formado por la
		// aguja y se lo sumo a la altura del extremo
		double y_2   = y + sin(theta);
		
		// Si este valor es mayor que 1, se cruzo con la linea de arriba,
		// y si es menor que cero con la de abajo.
		if( (y_2 >= 1) || (y_2 <= 0))
			A++;
	}

	cout.precision(9);
	cout << "El valor de PI a partir de la simulacion para " << N << " iteraciones es: " << (2.0*N)/A << endl;
	cout << "El valor de la libreria <cmath> es: " << M_PI << ".\n";

	return 0;
}

// Con amor, Cabre.