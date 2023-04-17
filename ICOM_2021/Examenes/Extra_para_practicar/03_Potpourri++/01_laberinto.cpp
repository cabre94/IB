#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Funcion para encontrar la entrada 'E' del laberinto y guardar los indices
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

/* Llena el el laberinto con 'o' para el camino a la salida. Tambien usamos un '-' para 
indicar una casilla que sabemos que no va a llegar a la salida*/
void floodFillLaberinto(vector<string> &laberinto, int i, int j, bool &solved){
	// Casos en donde volver: Si estoy en una pared. Si estoy afuera.
	if(solved)	// Si lo resolvimos, ya esta
		return;
	if(i < 0 || i >= laberinto.size() || j < 0 || j >= laberinto[i].size())	// Por si nos fuimos del tablero
		return;
	/*Chequeamos que no estemos en una pared, en un lugar marcado como '-' o el camino actual*/
	else if(laberinto[i][j] == '#' || laberinto[i][j] == '-' || laberinto[i][j] == 'o')
		return;
	else if(laberinto[i][j] == 'S'){	// Si llegamos a la salida
		solved = true;
		return;
	}
	else{
		laberinto[i][j] = 'o';	// Marcamos el camino actual
		floodFillLaberinto(laberinto, i, j+1, solved);	// Derecha
		floodFillLaberinto(laberinto, i+1, j, solved);	// Abajo
		floodFillLaberinto(laberinto, i, j-1, solved);	// Izquierda
		floodFillLaberinto(laberinto, i-1, j, solved);	// Arriba. Creo...
		/*Si no lo logramos resolver, marcamos esta casilla 
		con - indicando que desde aca no se puede llegar */
		if(!solved)	
			laberinto[i][j] = '-';
	}
}


vector<string> solve(vector<string> laberinto){
	// busco la posicion inicial. Asumo que siempre existe
	int i0, j0;
	getPosInicial(laberinto, i0, j0);

	bool solved = false;
	floodFillLaberinto(laberinto, i0, j0, solved);

	// Limpiamos del laberinto las casillas marcadas como '-'
	for(int i=0; i < laberinto.size(); i++){
		for(int j=0; j < laberinto[i].size(); j++){
			if(laberinto[i][j] == '-')
				laberinto[i][j] = ' ';
		}
	}

	return laberinto;
}

int main(){
    vector<string> laberinto;
	string line;

	// Leemos el laberinto
	ifstream datos("laberinto.txt");

    if(datos.is_open()){
        while(getline(datos, line)){
            laberinto.push_back(line);
        }
        datos.close();
    }

	// resolvemos el laberinto
	vector<string> laberintoSolved = solve(laberinto);

	// Printeamos el laberinto resuelto
	for(int i=0; i < laberintoSolved.size(); i++)
		cout << laberintoSolved[i] << endl;

    return 0;
}