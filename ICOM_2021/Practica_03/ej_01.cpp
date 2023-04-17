#include <iostream>
#include <ctime>

using namespace std;

double aproximacion_de_Pi(int N){

	int N1 = 0; // Variable para contar cuantos puntos hay adentro
	double x, y, dist;

	for(int i = 0; i < N; i++){
		// La simulacion en vez de hacerla en un cuadrado de -1 a 1 lo hacemos
		// solo en el primer cuadrante ya que la relacion deberia ser la misma.
		x = (double) rand()/RAND_MAX;
		y = (double) rand()/RAND_MAX;
		// rand() y RAND_MAX son enteros, asi que el cociente nos da la division
		// entera. Ademas, como rand() nos da un numero entre 0 y RAND_MAX, 
		// la division entera siempre nos da 0. Para evitar esto y obtener un
		// numero entre 0 y 1 como queremos, tenemos que "castear" a double
		// el cociente poniendo adelante el (double). Con esto lo que hacemos
		// es decirle al compilador que interprete el cociente como un double
		// en lugar de un entero y todos felices. Acostumbrate a esto ahora
		// porque no va a ser la primera ver que escuches la palabra castear.
		
		// Si cae adentro, aumentamos el contador. No hace falta sacar raiz
		// cuadrada.
		if(x*x + y*y <= 1)	
			N1++;
	}

	return (4.0*N1)/N;
	// return (double) 4*N1/N;	// Se obtiene lo mismo
}

int main(){
	srand(time(0)); // Inicializamos con una semilla aleatoria

	int N;
	cout << "Ingresar la cantidad de iteraciones a realizar: " << endl;
	cin >> N;

	cout << "El valor aproximado de Pi es: " << aproximacion_de_Pi(N) << endl;

	return 0;
}

// Con amor, Cabre.