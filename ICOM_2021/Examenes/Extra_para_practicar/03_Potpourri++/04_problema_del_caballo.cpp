/*
date: 20-10-21
File: 04_problema_del_caballo.cpp
Author : Facundo Martin Cabrera
Email: cabre94@hotmail.com facundo.cabrera@ib.edu.ar
GitHub: https://github.com/cabre94
GitLab: https://gitlab.com/cabre94
Description: 
*/

#include <iostream>
#include <iomanip>

using namespace std;

const int lado = 8;

// Va llenando el tablero con el numero de movida usando backtracking
void solve(short M[lado][lado], int i, int j, int step_count, bool &solved){
	if(solved)	// Si lo resolvimos, ya esta
		return;
	if(i < 0 || i >= lado || j < 0 || j >= lado)	// Por si nos fuimos del tablero
		return;
	else if(M[i][j] != 0)	// Chequeamos que no hayamos pasado por esta posicion
		return;
	else if(step_count == (lado*lado)){	// Si llegamos al ultimo movimiento
		M[i][j] = step_count;
		solved = true;
		return;
	}
	else{
		M[i][j] = step_count;	// Marcamos el numero de movida
		solve(M, i+2, j+1, step_count+1, solved);
		solve(M, i+2, j-1, step_count+1, solved);
		solve(M, i+1, j+2, step_count+1, solved);
		solve(M, i+1, j-2, step_count+1, solved);

		solve(M, i-1, j-2, step_count+1, solved);
		solve(M, i-1, j+2, step_count+1, solved);
		solve(M, i-2, j-1, step_count+1, solved);
		solve(M, i-2, j+1, step_count+1, solved);


		// Si no lo logramos resolver, marcamos esta casilla con 0
		// Puede ser que por otro recorrido pasando por esta casilla sea
		// posible llegar
		if(!solved)	
			M[i][j] = 0;
	}
}

void imprimeMatriz(short M[lado][lado]){
	for(int i=0; i < lado; i++){
		for(int j=0; j < lado; j++){
			// cout << setfill('0') << setw(2) << M[i][j] << ' ';
			cout << setw(2) << M[i][j] << ' ';
		}
		cout << endl;
	}
}


int main(){

	short tablero[lado][lado] = {0};

	bool solved = false;

	// Tarda un huevo esto, con un tablero de 7x7 lo hace al toque, no se
	// porque hay tanta diferencia con el de 8x8. ¿Capaz no hay solucion?
	// for(int i=0; (i < lado) && !solved; i++){
	// 	for(int j=0; (j < lado) && !solved; j++)
	// 		solve(tablero, i, j, 1, solved);
	// }

	// Pruebo con algunas posiciones
	solve(tablero, 0, 0, 1, solved);
	// solve(tablero, 1, 1, 1, solved);
	// solve(tablero, 1, 0, 1, solved);

	imprimeMatriz(tablero);

	return 0;
}