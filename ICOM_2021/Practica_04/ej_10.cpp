#include <iostream>

using namespace std;

int iteracion(int tamano);

int main(){
	srand(time(0));

	cout << "\nTamaño\tProbabilidad" << endl;
	
	// Para cada tamaño entre 10 y 60, genero 1000 grupos y veo en cuantos hay
	// gente que cumpla en un mismo dia
	for(int tamano = 10; tamano <= 60; tamano+=10){
		int contador = 0;
		for(int i=0; i < 1000; i++)			// Genero los 1000 grupos
			contador += iteracion(tamano);	// Sumo el resultado de la iteracion
		cout << tamano << "\t" << contador/10.0 << "%" << endl;
	}
	cout << endl;	// Necesito que quede prolijo porque tengo problemitas

	return 0;
}

// Funcion que genera un grupo de un tamaño dado. Devuelve 1 si hay mas de una
// persona que cumpla en un mismo dia y cero si todos cumplen en dias distintos.
int iteracion(int tamano){

	// Armo un array de enteros de 365 elementos para contar cuantas veces
	// aparece cada cumpleaños
	int dias[365] = {0}, dia;

	for(int i=0; i < tamano; i++){
		// Genero numero aleatorio entre 0 y 364
		dia = rand() % 365;
		// Le sumo uno a la cantidad de personas que cumplen en ese dia
		dias[dia]++;
		// Si para algun dia ya hay dos personas, devuelvo 1 para sumar al
		// contador del main
		if(dias[dia] > 1)			
			return 1;
	}

	return 0;				// Si ningun cumpleaños se repitio, devuelvo 0.
}

// Con amor, Cabre.