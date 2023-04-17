#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>		// Esta es para usar el istringstream
#include <exception>

using namespace std;

int main(){
	ifstream datos("peaks.dat");		// Abro el archivo

	double x, y, x_max, y_max;

	if(datos.is_open()){
		// Leemos los primeros dos y lo guardamos como os maximos
		datos >> x_max >> y_max;

		// Leemos dos doubles hasta que termine el archivo
		while(datos >> x >> y){
			// Si y > y_max, actualizamos el maximo y su posicion
			if(y > y_max){
				x_max = x;
				y_max = y;
			}
		}

		datos.close();	// cerramos el archivo
	}


	cout.precision(7);
	cout << "El valor maximo es y = " << y_max;
	cout << " y se encuentra en x = " << x_max << endl;

	return 0;
}

// Con amor, Cabre.