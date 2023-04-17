#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

// UDT para representar una casilla del tablero
struct Casilla {
    int salto; // longitud del salto desde esta casilla
    int nummov; // si la casilla forma parte de la solucion, el numero de movida
    bool visitada; // si la casilla ya fue visitada o no
};

// UDT que representa el juego
struct Saltarin
{
    static const int N = 10; // tamaño del tablero N x N
    Casilla tablero[N][N]; // representacion del tablero como matriz de casillas
    int nummov; // para llevar la cuenta de en que movida voy

	// Constructor que lee los saltos del archivo que recibe como argumento
    Saltarin(string file)
    {
		//TODO
	}

	// metodo recursivo que resuelve el juego a partir de la casilla {i,j}
    bool resolver(int i, int j)
    {
		//TODO
    }

	// imprime el tablero, con la info del salto y nummov de cada casilla
    void print()
    {
		//TODO
    }

};

int main()
{
    cout << "Uno con salida " << endl;
    string file = "consalida.txt";
    Saltarin salta(file);
    salta.print();
    if (!salta.resolver(0,0))
    {
        cout << "No hay salida " << endl;
    }
    else
    {
        cout << "Encontre la salida " << endl;
        salta.print();
    }

    cout << endl<<"Uno sin salida " << endl;

    file = "sinsalida.txt";
    Saltarin salta2(file);
    salta2.print();
    if (!salta2.resolver(0,0))
    {
        cout << "No hay salida " << endl;
    }
    else
    {
        cout << "Encontre la salida " << endl;
        salta2.print();
    }

    return 0;
}
