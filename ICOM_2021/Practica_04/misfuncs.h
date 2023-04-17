#include <iostream>
#include <cmath>
#include <array>
#include <vector>

using namespace std;

// ============================================================= //
// FUNCIONES QUE IMPRIMEN E INGRESAN VALORES A UN VECTOR O ARRAY //
// ============================================================= //

// Para arreglos nativos de doubles
void ImprimeVector(double Vector[], int NumElementos);
void IngresaVector(double Vector[], int NumElementos);
// Imprime un arreglo nativo de enteros
void ImprimeVector(int Vector[], int NumElementos);

/* Para vectores
Es importante a la funcion pasarle la referencia del vector (o sea, ponerle
el & en el argumento). Pasar por referencia un argumento lo que hace es
mandarle el argumento original en lugar de una copia. Esto sirve si queres
modificar el argumento original, como es el caso.
Esto para la funcion ImprimeVector en realidad no importa mucho, ya que
imprimir en pantalla la copia o el original da igual. Como extra para que quede
bien, la funcion imprime vector no va a modificar el vector, asi que le podemos
poner const adelante*/
void IngresaVector(vector<double> &Vector);
void ImprimeVector(const vector<double> &Vector);
/* Ahora, ¿porque no hace falta esto mismo para los arrays nativos? es porque
funcionan distinto. El nombre de un array nativo es la direccion de memoria
al primer elemento del array, pero esa direccion de memoria es la de los
elementos originales.*/


// Para arrays con la libreria <array>
// Aca estoy haciendo una version template para que el largo sea variable.
// Es un tema que se va a ver mas adelante, asi que si no se entiende pasalo.
// Las definiciones de las funciones templates tienen que ir en el .h, no en
// el .cpp. Creo que existe alguna forma de hacerlo como el resto de las
// funciones no templates, pero es algo que me supera (y dudo que importe en
// ICOM)
// Misma historia con el tema de las copias y referencias.

template<size_t N>
void ImprimeVector(array<double, N> &arr){
	if(arr.size() <= 0) return;
	for(size_t i=0; i < arr.size()-1; i++)
		cout << arr[i] << ' ';
	cout << arr[arr.size()-1] << endl;
}

template<size_t N>
void IngresaVector(array<double, N> &arr){
	cout << "Ingrese los elementos del vector de dimension " << arr.size();
	cout << " de a uno por vez.\n";
	for(size_t i=0; i < arr.size(); i++)
		cin >> arr[i];
}

// ============================================================= //
//                   FUNCIONES DE ORDENAMIENTO                   //
// ============================================================= //

// Ordena array nativo de enteros en forma creciente
void OrdenaArrayNativo(int V[], int n);
// Ordena array nativo de doubles en forma creciente
void OrdenaArrayNativo(double V[], int n);
// Invierte los elementos de un array nativo de enteros
void InvierteArrayNativo(int V[], int n);

// ============================================================= //
//                    FUNCIONES DE ESTADISTICA                   //
// ============================================================= //

// Funcion que calcula el promedio de un conjunto de doubles
double promedio(double datos[], int n);
// Funcion que calcula el desvio standard de un conjunto de doubles
double dstandard(double datos[], int n);

// Con amor, Cabre.