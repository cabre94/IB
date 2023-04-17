#include <iostream>

using namespace std;


void imprimeDigito(int num){
	if(num < 10){
		cout << num;
	}else{
		cout << (char) ('A'+num-10);
	}
}

void ImprimeEnBase(int valor, int base){
	if (valor >= base){
        ImprimeEnBase(valor/base, base);
	}
    imprimeDigito(valor % base);
}


int main(){

	int valor, base;

	while(true){
		cout << "Ingrese numero en base decimal (-1 para terminar)" << endl;
		cin >> valor;

		if(valor == -1)
			break;

		cout << "Ingrese la base en la que lo quiere expresar (2-16)" << endl;
		cin >> base;

		cout << valor << " en base " << base << " es ";
		ImprimeEnBase(valor, base);
		cout << endl;
	}
	cout << "Bye bye\n";

	return 0;
}

// Con amor, Cabre.