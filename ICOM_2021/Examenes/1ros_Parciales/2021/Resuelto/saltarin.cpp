#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

// UDT para representar una casilla del tablero
struct Casilla{
    int salto; // longitud del salto desde esta casilla
    int nummov; // si la casilla forma parte de la solucion, el numero de movida
    bool visitada; // si la casilla ya fue visitada o no
};

// UDT que representa el juego
struct Saltarin{
    static const int N = 10; // tamaño del tablero N x N
    Casilla tablero[N][N]; // representacion del tablero como matriz de casillas
    int nummov; // para llevar la cuenta de en que movida voy

	// Constructor que lee los saltos del archivo que recibe como argumento
    Saltarin(string file);

	// metodo recursivo que resuelve el juego a partir de la casilla {i,j}
    bool resolver(int i, int j);

	// imprime el tablero, con la info del salto y nummov de cada casilla
    void print();
};

int main(){
    cout << "Uno con salida " << endl;
    string file = "consalida.txt";
    Saltarin salta(file);
    salta.print();
    if (!salta.resolver(0,0)){
        cout << "No hay salida " << endl;
    }else{
        cout << "Encontre la salida " << endl;
        salta.print();
    }

    cout << endl<<"Uno sin salida " << endl;

    file = "sinsalida.txt";
    Saltarin salta2(file);
    salta2.print();
    if (!salta2.resolver(0,0))    {
        cout << "No hay salida " << endl;
    }else{
        cout << "Encontre la salida " << endl;
        salta2.print();
    }

    return 0;
}


Saltarin::Saltarin(string file){
	nummov = 0;

	ifstream ifile(file);

	if(ifile.is_open()){
		int salto;
		for(int i=0; i < N; i++){
			for(int j=0; j < N; j++){
				ifile >> salto;
				tablero[i][j] = {salto, -1, false};
			}
		}
		ifile.close();	// Cierro el archivo
	}
}

// metodo recursivo que resuelve el juego a partir de la casilla {i,j}
bool Saltarin::resolver(int i, int j){
	// Primero chequeamos estar dentro del tablero.
	// Lo hago en mas de un if para que sea mas claro, pero se puede hacer en uno.
	if(i < 0 || i >= N)
		return false;
	if(j < 0 || j >= N)
		return false;
	// Si esta visitada, tampoco nos sirve
	if(tablero[i][j].visitada)
		return false;
	
	// Si llegamos aca, la casilla es valida, asi que la marcamos como visitada
	// y aumentamos en 1 el contador
	tablero[i][j].visitada = true;	// Visitada
	tablero[i][j].nummov = nummov;	// ponemos el num de paso en esta casilla
	nummov++;		// Aumentamos el contador
	
	// Si llegamos a la salida, retornamos true y terminamos
	if(i==N-1 && j==N-1)
		return true;

	// Ahora tenemos que movernos, para eso necesitamos el salto de la casilla
	int salto = tablero[i][j].salto;
	// Nos movemos recursivamente en todas las direcciones y si alguna retorno
	// true, es porque por ahi se llega.
	if(resolver(i+salto, j) || resolver(i-salto, j))
		return true;
	if(resolver(i, j+salto) || resolver(i, j-salto))
		return true;
	
	// Si llegamos aca, entonces por esta casilla no se llega a la salida
	// La dejamos como visitada, para no volver, PERO le cambiamos nummov
	// porque en definitiva por aca no se llega
	tablero[i][j].nummov = -1;
	return false;
}

// imprime el tablero, con la info del salto y nummov de cada casilla
void Saltarin::print(){
	for(int i=0; i < N; i++){
		for(int j=0; j < N; j++){
			cout << tablero[i][j].salto;
			if(tablero[i][j].nummov != -1)
				cout << " ("<<tablero[i][j].nummov << ")";
			cout << "\t";
		}
		cout << endl;
	}
}