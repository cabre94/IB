#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// Dejo el numero de figuras de las cartas como un macro para que sea facil de modificar
#define NUM_FIGURAS 8

class Mazo {
	public:
		// Construye una instancia de Mazo leyendo las 'cartas' a partir la 
	    // informaci�n le�da en el 'iFile'.
		// El archivo cuenta con un string por rengl�n, con los s�mbolos de la
		// carta
		Mazo(const string &fname);                    // TODO

		// M�todo que verifica que todo par de cartas del mazo tenga un solo 
		// elemento en com�n.
		bool esValido();                              // TODO

		//Funci�n que imprime el mazo
		void print();						          // TODO

	private:
		// representacion de todas las cartas
		vector<string> cartas;

		// M�todo que retorna la cantidad de s�mbolos comunes entre las cartas
		// en las posici�n i y j
		unsigned int coincidencias(int i, int j);     // TODO

		// Funcion auxiliar que verifica que todas las cartas tengan 8 figuras diferentes
		bool validLenght();
};

int main(){
	Mazo m("mazo.txt");

	m.print();

	cout << "el mazo es " << (m.esValido() ? "VALIDO" : "INVALIDO") << endl;

	return 0;

}

Mazo::Mazo(const string &fname){
	ifstream mazo(fname);		// Abro el archivo
	string carta;

	if(mazo.is_open()){
		while (mazo >> carta){
			cartas.push_back(carta);
		}
        mazo.close();
    }
}

bool Mazo::esValido(){
	// Primero chequeamos cada carta con la funcion auxiliar
	if(!validLenght())
		return false;
	
	// Ahora, para cada par de cartas, tenemos que chequear que haya solo una figura en comun
	for(int i=0; i < cartas.size()-1; i++){
		for(int j=i+1; j < cartas.size(); j++){
			if(coincidencias(i, j) != 1){
				cout << cartas[i] << " -" << cartas[j] << "-" << j << endl;
				return false;
			}
		}
	}

	// si llegamos a este punto, todas las cartas tienen una sola coincidencias con otras
	return true;
}

void Mazo::print(){	
	if(cartas.size()){
		for(int i=0; i < cartas.size(); i++)
			cout << i << ": " << cartas[i] << endl;
	}else
		cout << "Mazo vacio" << endl;
}

unsigned int Mazo::coincidencias(int i, int j){
	unsigned int res = 0;
	for(int idx1 = 0; idx1 < cartas[i].size(); idx1++){
		for(int idx2 = 0; idx2 < cartas[j].size(); idx2++){
			if(cartas[i][idx1] == cartas[j][idx2])
				res++;
		}
	}
	return res;
}

bool Mazo::validLenght(){
	for(int i=0; i < cartas.size(); i++){
		// Primero chequeamos que el largo sea el correcto
		if(cartas[i].size() != NUM_FIGURAS)
			return false;
		
		// Ahora chequeamos que las 8 figuras sean distintas
		for(int j=1; j < NUM_FIGURAS; j++){
			for(int k=0; k < j; k++){
				if(cartas[i][j] == cartas[i][k])
					return false;
			}
		}
	}
	return true;
}