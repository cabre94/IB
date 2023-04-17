#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>



using namespace std;


struct GenFrase{
	enum TipoPalabra {ARTICULO, SUSTANTIVO, VERBO, PREPOSICION};

	vector<string> articulos;
	vector<string> sustantivos;
	vector<string> verbos;
	vector<string> preposiciones;

	void cargaConjuntos(const string &fname_articulos, const string &fname_sustantivos,
						const string &fname_verbos, const string &fname_preposiciones);
	
	string generaFrase(const vector<TipoPalabra> &estructura_frase);
};

int main(){
	srand(time(0));

	GenFrase kk;

	kk.cargaConjuntos("articulos.txt", "sustantivos.txt", "verbos.txt", "preposiciones.txt");
	// "/home/cabre/Desktop/ICOM/ICOM_2021/1er_Parcial/2019/Resuelto/Ej2/articulos.txt";


	/*for(int i=0; i < kk.articulos.size(); i++){
		cout << kk.articulos[i] << " ";
	}
	cout << endl;

	for(int i=0; i < kk.verbos.size(); i++){
		cout << kk.verbos[i] << " ";
	}
	cout << endl;

	for(int i=0; i < kk.sustantivos.size(); i++){
		cout << kk.sustantivos[i] << " ";
	}
	cout << endl;

	for(int i=0; i < kk.preposiciones.size(); i++){
		cout << kk.preposiciones[i] << " ";
	}
	cout << endl;*/

	vector<GenFrase::TipoPalabra> estructura_frase = {GenFrase::ARTICULO, GenFrase::SUSTANTIVO, GenFrase::VERBO, GenFrase::PREPOSICION};

	string frase =  kk.generaFrase(estructura_frase);

	cout << frase << endl;


}


void GenFrase::cargaConjuntos(const string &fname_articulos, const string &fname_sustantivos,
						const string &fname_verbos, const string &fname_preposiciones){
	
	string palabra;
	
	ifstream file(fname_articulos);		// Abro el archivo
	if(file.is_open()){
		while (file >> palabra)
			articulos.push_back(palabra);
        file.close();
    }

	file.open(fname_sustantivos);
	if(file.is_open()){
		while (file >> palabra)
			sustantivos.push_back(palabra);
        file.close();
    }

	file.open(fname_verbos);
	if(file.is_open()){
		while (file >> palabra)
			verbos.push_back(palabra);
        file.close();
    }

	file.open(fname_preposiciones);
	if(file.is_open()){
		while (file >> palabra)
			preposiciones.push_back(palabra);
        file.close();
    }

}

string GenFrase::generaFrase(const vector<TipoPalabra> &estructura_frase){
	string frase;
	int idx;

	for(int i=0; i < estructura_frase.size(); i++){
		switch(estructura_frase[i]){
			case ARTICULO:
				idx = rand() % articulos.size();
				frase.append(articulos[idx]);
				break;
			case SUSTANTIVO:
				idx = rand() % sustantivos.size();
				frase.append(sustantivos[idx]);
				break;
			case VERBO:
				idx = rand() % verbos.size();
				frase.append(verbos[idx]);
				break;
			case PREPOSICION:
				idx = rand() % preposiciones.size();
				frase.append(preposiciones[idx]);
				break;
			default:
				break;  // si llega hasta aca debería disparar una excepcion, pero paja y no lo piden.
		}
		frase.append(" ");
	}

	frase[0] = toupper(frase[0]);
	frase[frase.size()-1] = '.';


	return frase;
}
