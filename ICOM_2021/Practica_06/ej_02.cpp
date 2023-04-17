#include <iostream>

using namespace std;

// Calcula el maximo comun divisor entre dos numero de manera recursiva
int MCD(int A, int B);
// Calcula el minimo comun multiplo entre dos numero de manera recursiva
int MCM(int A , int B);

int main(){
	int A,B;

	cout << "Ingrese A:" << endl;
	cin >> A;
	cout << "Ingrese B:" << endl;
	cin >> B;

	cout << "Si mandas numeros muy falopa puede tardar un rato" << endl;

	cout << "El MCD entre " << A << " y " << B << " es: " << MCD(A,B) << endl;

	cout << "El MCM entre " << A << " y " << B << " es: " << MCM(A,B) << endl;

	return 0;   
}

// El caso base: es el hint que nos dan. Cuando un numero es 0, entonces el
// MCD entre X y 0 es X. En el ejercicio tomamos que A>=B, entonces el caso base
// se da cuando B es 0. En ese caso, retornamos A.
// La recursion:
// - Nos dicen que MCD(A, B) == MCD(B, A%B), asi que la recursion deberia estar
// medianamente clara en este caso.
// - La regla que nos dan es para  A >= B. Si B > A intercambiamos los
// argumentos y fue
int MCD(int A, int B){
	if(B > A)
		MCD(B,A);
	if(B == 0)
		return A;
	else
		return MCD(B, A%B);
}

int MCM(int A , int B){
	int res = (A*B) / MCD(A,B);
	return res;
}

// Con amor, Cabre.