#include <iostream>

using namespace std;

int main(){
	// long int i;
	int i;

	// Hacemos primero la sumatoria con floats
	float s= 0, x1 = 1.126, x2 = -1.125, x3 = -0.001;
	for(i = 1; i <= 0xFFFFFF; i++)
		s += x1 + x2 + x3;
    cout << "Usando floats la sumatoria dio: " << s << ".\n";

    // Ahora hacemos el calculo con doubles
    double S = 0, X1 = 1.126, X2 = -1.125, X3 = -0.001;
    for(i = 1; i <= 0xFFFFFF; i++)
    	S += X1 + X2 + X3;
    cout << "Usando doubles la sumatoria dio: " << S << ".\n";

	return 0;
}

/*
El 0x indica que la notacion del numero es en hexadecimal, se puede usar direc
tamente el 0xFFFFFF para el for en lugar de tener que calcular que numero es
en decimal.

Al margen de eso, la idea del ejercicio es que veas que la sumatoria deberia
dar cero, pero que todas las operaciones de punto flotante inducen errores
porque la maquina no puede almacenar todos los numeros de manera exacta
(depende el numero igual, el 0.1 en notacion decimal es exacto, pero en binario,
que es en definiva el sistema que usa la maquina, es un numero periodico).

Con float esos errores son mayores porque se usa menos memoeria y se puede
representar menos cifras significativas
*/

// Con amor, Cabre.