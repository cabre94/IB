// #include "icom_helpers.h"
#include <iostream>
#include <vector>

using namespace std;

class Monedero{
public:
	// construye un monedero con las distintas denominaciones
	// a manejar expresadas en centavos. Por ejemplo si se van a manejar
	// las siguientes denominaciones: $0.50, $1, $2, $10, $50, $100 y $500
	// podría construirse con el vector
	// {50, 100, 200, 2000, 5000, 10000, 50000}
	Monedero(const vector<int> &valorMonedas);
	// Agrega un sueldo a ser distribuido en las distintas
	// denominaciones, se debe minimizar la cantidad de
	// billetes/monedas a entregar
	void agregaSueldo(double montoSueldo);
	// Retorna la cantidad de billetes/monedas necesarios de la
	// denominacion de valor 'denominacion'
	int cantidadValor(int denominacion);
	void print();			// printea monedero
private:
	struct Denominacion {
		int valor;			// valor de la denominación en centavos
		int cantidad; 		// cantidad de billetes/moneda necesarios
	};
	vector<Denominacion> monedas; 	// denominaciones a utilizar

	// Una struct para lanzar como excepcion en caso de no encontrar una
	// denominacion
	struct denominationNotFound{};
	
};

int main(){
	vector<int> billetes = {1,5,10,25,50,100,200,500,1000,2000,5000,10000,20000,50000,100000};
	Monedero mone(billetes);

	double sueldo;
	cout << "Ingrese sueldo:" << endl;
	cin >> sueldo;
	mone.agregaSueldo(sueldo);

	cout << endl << "El monedero tiene:" << endl << endl;
	mone.print();

	return 0;
}

Monedero::Monedero(const vector<int> &valorMonedas){
	for(size_t i=0; i < valorMonedas.size(); ++i)
		monedas.push_back({valorMonedas[i], 0});
}

// Nunca se aclara explicitamente, pero para que tenga sentido que el argumento
// sea un double, uno pensaria que los decimales corresponden a centavos, asi
// que hay que multiplicar por 100 para obtener los equivalente a valorModedas
void Monedero::agregaSueldo(double montoSueldo_){
	// No te comas el segundo parentesis
	int montoSueldo = (int) (montoSueldo_ * 100);

	for(int i = monedas.size()-1; i >= 0; i--){
		// Todas la variables son enteras, asi que la division en la division entera
		monedas[i].cantidad = montoSueldo / monedas[i].valor;
		montoSueldo = montoSueldo % monedas[i].valor;
	}	
}

int Monedero::cantidadValor(int denominacion){
	for(int i = monedas.size()-1; i >= 0; i--){
		if(monedas[i].valor == denominacion)
			return monedas[i].cantidad;
	}
	throw denominationNotFound{};
}

void Monedero::print(){
	for(int i = monedas.size()-1; i >= 0; i--){
		cout << cantidadValor(monedas[i].valor) << "\tmonedas/billetes de $";
		cout << monedas[i].valor / 100.0 << endl;
	}
}

// Con amor, Cabre.