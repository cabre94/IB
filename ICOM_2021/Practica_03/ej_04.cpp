#include <iostream>

using namespace std;

int main(){
	int nc = 0, np = 0, nl = 0, c;
	bool kk = false;
	// La variable kk es auxiliar y es para no contar una palabra si hay,
	// por ejemplo, dos salto de lineas seguidos.
	// Le asigno k=0 cuando termina una palabra. De manera de sumar uno al
	// contador de palabras cuando se haya leido una letra y sea k=0.
	
	// El parentesis de (c = cin.get()) es necesario, me cago la vida ese error.
	while( (c = cin.get()) != EOF){
		nc++;
		if(c == '\n'){
			nl++;
		}
		if(c == '\n' || c == ' ' || c == '\t'){
			kk = false;
		}else{
			if(!kk){
				np++;
				kk = true;
			}
		}
	}

	cout << "Se leyeron " << nc << " caracteres, ";
	cout << np << " palabras y ";
	cout << nl << " lineas." << endl;
	
	return 0;
}

// En linux, la terminal entiende como EOF haciendo ctrl+D. La otra es darle
// un archivo para que lea.
// Dejo una de ejemplo que se puede correr haciendo las siguientes dos lineas
// g++ ej_04.cpp -o exe
// ./exe < ej_04.txt

// Con amor, Cabre.