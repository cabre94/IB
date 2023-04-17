#include <iostream>

using namespace std;

void imprimir_secuencia(int N, int M){
	for(int i=0; i <= M; i++){
		for(int j=0; j <= N; j++){
			cout << i << j << "\t";
		}
		cout << endl;
	}
}

int main(){

	int N, M;

	cout << "Ingresar N: " << endl;
	cin >> N;
	cout << "Ingresar M: " << endl;
	cin >> M;
	cout << endl;

	imprimir_secuencia(N, M);

	return 0;
}

// Con amor, Cabre.