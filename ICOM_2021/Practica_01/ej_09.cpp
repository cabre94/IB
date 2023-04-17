#include <iostream>

using namespace std;

double evaluar_polinomio(double x){
	return 3*x*x*x -5*x*x + 6;
}

int main (){
	double x;

	cout << "Ingrese x: " << endl;
	cin >> x;

	cout << "3x^2 - 5x^2 + 6 evaluado en x = " << x << " es" << endl;
	cout << evaluar_polinomio(x) << endl;
}

// Con amor, Cabre.