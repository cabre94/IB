#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum Direccion{DER /*0*/, ARR, ABA, IZQ, NUM_DIR};



// asumo que el laberinto siempre es cuadrado y tiene una E y una S
void getPosInicial(vector<string> &laberinto, int &i0, int &j0){
	for(int i=0; i < laberinto.size(); i++){
		for(int j=0; j < laberinto[i].size(); j++){
			if(laberinto[i][j] == 'E'){
				i0 = i;
				j0 = j;
				return;
			}
		}
	}
}

// Direccion



vector<string> solve(vector<string> laberinto){
	vector<Direccion> camino;

	// busco la posicion inicial. Asumo que siempre existe
	int i, j;
	getPosInicial(laberinto, i, j);

	while(laberinto[i][j] != 'S'){

		for(int k=0; k < NUM_DIR; k++){	// arriba, abajo, izquirda, derecha
			// Direccion(k); // (Direccion) i;

			// Chequear que la posicion es valida. #, -, o
		}

	}

	switch (dir){
	case DER:
		laberinto[i][j] = 'o';
		j++
		break;
	
	default:
		break;
	}



	




	return laberinto;
}








int main(){
	ifstream datos("laberinto.txt");		// Abro el archivo

    vector<string> laberinto;
	string line;

    if(datos.is_open()){

        while(getline(datos, line)){
            laberinto.push_back(line);
        }

        datos.close();
    }

	vector<string> laberintoSolved = solve(laberinto);





	// for(int i=0; i < laberinto.size(); i++){
	// 	cout << laberinto[i] << endl;
	// }

	for(int i=0; i < laberintoSolved.size(); i++){
		cout << laberintoSolved[i] << endl;
	}



    return 0;
}


