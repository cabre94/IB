#include "icom_helpers.h"

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
};

int main(){
	vector<int> billetes = {1,2,5,10,20,50,100,200,500,1000};
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
	int N = valorMonedas.size();
	monedas.resize(N);
	for(int i=0; i < N; i++){
		monedas[i].valor = valorMonedas[i];
		monedas[i].cantidad = 0;
	}
}

void Monedero::agregaSueldo(double montoSueldo){
	for(int i = monedas.size()-1; i >= 0; i--){
		monedas[i].cantidad = (int) montoSueldo / monedas[i].valor;
		montoSueldo = (int) montoSueldo % monedas[i].valor;
	}
}

int Monedero::cantidadValor(int denominacion){
	for(int i = monedas.size()-1; i >= 0; i--){
		if(monedas[i].valor == denominacion)
			return monedas[i].cantidad;
	}
}

void Monedero::print(){
	for(int i = monedas.size()-1; i >= 0; i--)
		cout << cantidadValor(monedas[i].valor) << "\tmonedas/billetes de $" << monedas[i].valor << endl;
}



// Con amor, Cabre.