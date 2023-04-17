#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// UDT para representar una casilla del tablero
struct Casilla
{
    int salto; // longitud del salto desde esta casilla
    int nummov; // si la casilla forma parte de la solucion, el numero de movida
    bool visitada; // si la casilla ya fue visitada o no
};

// UDT que representa el juego
struct Saltarin
{
    static const int N = 10; // tama�o del tablero N x N
    Casilla tablero[N][N]; // representacion del tablero como matriz de casillas
    int nummov; // para llevar la cuenta de en que movida voy

    // Constructor que lee los saltos del archivo que recibe como argumento
    Saltarin(string file)
    {
        nummov=0;
        ifstream ifile(file);
        if(!ifile.is_open())
            throw string("Error: no pude abrir el archivo ") + file;

        int salto;
        for (int i=0; i<N; ++i)
            for(int j=0; j<N; ++j)
            {
                ifile >> salto;
                tablero[i][j]= {salto, -1, false};
            }

    }

    // metodo recursivo que resuelve el juego a partir de la casilla {i,j}
    bool resolver(int i, int j)
    {
        if(i<0||j<0||i>=N||j>=N||tablero[i][j].visitada==true)
            return false;

        tablero[i][j].visitada=true;
        tablero[i][j].nummov=nummov++;

        if(i==N-1 && j==N-1)
            return true;

        int salto=tablero[i][j].salto;
        if(resolver(i+salto,j)||resolver(i-salto,j)||resolver(i,j+salto)||resolver(i,j-salto))
            return true;

        tablero[i][j].nummov=-1;
        return false;

    }

    // imprime el tablero, con la info del salto y nummov de cada casilla
    void print()
    {
        for(int i=0; i<N; ++i)
        {
            for(int j=0; j<N; ++j)
            {
                cout << tablero[i][j].salto;
                if(tablero[i][j].nummov>=0)
                    cout << " ("<<tablero[i][j].nummov << ")";
                cout << '\t';
            }
            cout << endl;
        }
    }

};

int main()
{
    cout << "Uno con salida " << endl;
    string file = "consalidaa.txt";
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
