#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <array>
#include <vector>
#include <algorithm>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;

double promedio(double datos[], int n);
double dstandard(double datos[], int n);

int main(){
	double arr[3] = {2, 4, 7};

	cout << "El promedio es: " << promedio(arr,3) << endl;
	cout << "La desviacion standar: " << dstandard(arr,3) << endl;

	return 0;
}

// Funcion que calcula el promedio de un conjunto de doubles
double promedio(double datos[], int n){
	double suma = 0;

	for(int i=0; i < n; i++)
		suma += datos[i];
	return suma/n;
}

// Funcion que calcula el desvio standard de un conjunto de doubles
double dstandard(double datos[], int n){
	double suma = 0;
	double X = promedio(datos,n);

	for(int i=0; i < n; i++)
		suma += (datos[i] - X) * (datos[i] - X);
	return sqrt(suma/(n-1));
}

// Con amor, Cabre.