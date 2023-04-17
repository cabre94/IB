#include <iostream>

using namespace std;

int suma(int N){
	int res=0;

	for (int i=1 ; i <= N ; i++)
		res += i;
	
	return res;
}


int main(){
	int N;
	cout << "Suma los primeros N numeros. Ingresar N:\n";
	cin >> N;
	cout << "La suma de los primeros N numeros es: " << suma(N) << endl; // endl = "\n"
	return 0;
}

// Con amor, Cabre.