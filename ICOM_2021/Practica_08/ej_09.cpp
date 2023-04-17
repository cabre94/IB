#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>		// Para la funcion qsort
// qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
// Argumentos:
// - Base: es el puntero al array que se quiere ordenar
// - nmemb: es el numero de elementos que tiene 'Base'. En general, un truco para
// sacar el numero de elementos de un array de cosas es hacer sizeof(array)/sizeof(cosas).
// - size: es el tamano de los elementos de 'Base'. Si es un array de double seria sizeof(double), por ejemplo.
// - int (*compar)(const void *, const void *): Es un puntero a funcion. A esto le tenemos que mandar un puntero
// a la funcion que va a tener el criterio con el que se van a ordenar los elementos de 'Base'.
// Esa funcion tiene que devolver un entero -1, 0 o 1. Ademas, para hacerla
// super general, toma dos punteros a void. De manera de poder recibir cualquier cosa.

using namespace std;

typedef struct {
	int i;
	int j;
	int value;
} Terna;

int compara_value(const void *a, const void *b);

int ordena_dist(const void *a, const void *b);


int main(){
	srand(time(0));		// Semilla del generador de numeros aleatorios

	Terna v[5];
	int size = sizeof(v) / sizeof(Terna);	// Calculo el numero de elementos del array v. Ahora es medio estupido porque ya se sabe
											// que es 10, pero esta es una manera general de calcularlo

	cout << "i\tj\tValue" << endl;
	// Inicializo todas las ternas con valores random
	for(int k=0; k < size; k++){
		v[k].i = rand() % 100;
		v[k].j = rand() % 100;
		v[k].value = rand() % 1000;
		cout << v[k].i << "\t" << v[k].j << "\t" << v[k].value << endl;
	}


	cout << "\n\nDespues de ordenarlos segun el atributo 'value':\n";
	qsort(v, size, sizeof(Terna), compara_value);

	cout << "i\tj\tValue" << endl;
	for(int k=0; k < size; k++)
		cout << v[k].i << "\t" << v[k].j << "\t" << v[k].value << endl;


	cout << "\n\nDespues de ordenarlos segun la distancia entre i y j:\n";
	qsort(v, size, sizeof(Terna), ordena_dist);

	cout << "i\tj\tValue\tDistancia" << endl;
	for(int k=0; k < size; k++){
		double d = sqrt(v[k].i*v[k].i + v[k].j*v[k].j);
		cout << v[k].i << "\t" << v[k].j << "\t" << v[k].value << '\t' << d << endl;
	}

	return 0;
}


int compara_value (const void *a, const void *b){
	Terna *p1 = (Terna *)a;
	Terna *p2 = (Terna *)b;
	return p1->value - p2->value;
}

int ordena_dist (const void *a, const void *b){
	Terna *p1 = (Terna *)a;
	Terna *p2 = (Terna *)b;

	double d12 = (p1->i * p1->i) + (p1->j * p1->j);
	double d22 = (p2->i * p2->i) + (p2->j * p2->j);

	if(d12 < d22)
		return -1;
	else if(d12 > d22)
		return 1;
	else
		return 0;
}

/*
Usar punteros a void permite programar funciones que tomar datos genericos.
Uno, en las funciones que toman esos void*, tiene que conocer que es lo que
contienen realmente y castearlo a ese tipo de puntero. Por ejemplo, en
ordena_dist los void* sabemos que son Terna*.

Cuando ponermos (Terna*) lo que hacemos es castear el puntero a lo que sabemos
que es. Es como cuando casteamos (double) rand()/RAND_MAX para que nos de un
numero entre 0 y 1. Despues, guardamos ese casteo en un Terna*, o sea, p1.

*/

// Con amor, Cabre.