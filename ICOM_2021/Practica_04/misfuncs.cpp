#include <iostream>
#include <cmath>
#include <array>
#include <vector>

using namespace std;

// Deje muchos comentarios en el .h que deberias ver antes de mirar este .cpp

// ============================================================= //
// FUNCIONES QUE IMPRIMEN E INGRESAN VALORES A UN VECTOR O ARRAY //
// ============================================================= //

// Para ARREGLOS NATIVOS
// Imprime un arreglo nativo de doubles
void ImprimeVector(double Vector[], int NumElementos){
	if( NumElementos <= 0) return;
	for(int i=0; i < NumElementos-1; i++)
		cout << Vector[i] << ' ';
	cout << Vector[NumElementos-1] << endl;
}

// Imprime un arreglo nativo de enteros
void ImprimeVector(int Vector[], int NumElementos){
	if( NumElementos <= 0) return;
	for(int i=0; i < NumElementos-1; i++)
		cout << Vector[i] << ' ';
	cout << Vector[NumElementos-1] << endl;
}

void IngresaVector(double Vector[], int NumElementos){
	cout << "Ingrese los elementos del vector de dimension " << NumElementos;
	cout << " de a uno por vez.\n";
	for(int i=0; i < NumElementos; i++)
		cin >> Vector[i];
}

void ImprimeVector(const vector<double> &vec){
	if(vec.size() <= 0) return;
	for(size_t i=0; i < vec.size()-1; i++)
		cout << vec[i] << ' ';
	cout << vec[vec.size()-1] << endl;
}

void IngresaVector(vector<double> &vec){
	cout << "Ingrese los elementos del vector de dimension " << vec.size();
	cout << " de a uno por vez.\n";
	for(size_t i=0; i < vec.size(); i++)
		cin >> vec[i];
}

// ============================================================= //
//                   FUNCIONES DE ORDENAMIENTO                   //
// ============================================================= //

// Ordena array nativo de enteros en forma creciente
void OrdenaArrayNativo(int V[], int n){
	int aux;
	for(int i=n-1; i>0; i--){
		for(int j=0; j < i; j++){
			if(V[j] > V[j+1]){
				aux = V[j];
				V[j] = V[j+1];
				V[j+1] = aux; 
			}
		}
	}
	return;
}

// Ordena array nativo de doubles en forma creciente
void OrdenaArrayNativo(double V[], int n){
	double aux;
	for(int i=n-1; i>0; i--){
		for(int j=0; j < i; j++){
			if(V[j] > V[j+1]){
				aux = V[j];
				V[j] = V[j+1];
				V[j+1] = aux; 
			}
		}
	}
	return;
}

// Invierte los elementos de un array nativo de enteros
void InvierteArrayNativo(int V[], int n){
	int aux;
	for(int i=0; i < (n/2); i++){
		aux = V[i];
		V[i] = V[n-1-i];
		V[n-1-i] = aux;
	}
}

// ============================================================= //
//                    FUNCIONES DE ESTADISTICA                   //
// ============================================================= //

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