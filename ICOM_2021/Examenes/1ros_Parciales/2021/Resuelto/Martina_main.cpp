#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>


using namespace std;

// UDT para representar una casilla del tablero
struct Casilla {
    int salto; // longitud del salto desde esta casilla
    int numpos; // si la casilla forma parte de la solucion, el numero de movida
    bool visitada; // si la casilla ya fue visitada o no
};

// UDT que representa el juego
struct Saltarin{
    static const int N = 10; // tamaño del tablero N x N
    Casilla tablero[N][N]; // representacion del tablero como matriz de casillas
    int nummov; // para llevar la cuenta de en que movida voy
    bool c,d,e,f;

	// Constructor que lee los saltos del archivo que recibe como argumento
    Saltarin(string file)
    {
        ifstream ifile (file);
        int salto;

        if (ifile.is_open()){

        for(int i=0; i<N;i++){
            for(int j=0;j<N;j++){
                ifile>>salto;
                tablero[i][j]={salto,-1,false};
            }

        }
        ifile.close();
	}
    }

	// metodo recursivo que resuelve el juego a partir de la casilla {i,j}
    bool resolver(int i, int j)
    {
        //cout<<i<<" "<<j<<endl;
        if (i>N-1 || i<0 || j>N-1 || j<0 ){
            return false;
        }
        if (tablero[i][j].visitada){
            return false;
        }
        if(i==N-1 && j==N-1){
            cout<<" a ver"<<endl;
            tablero[i][j].visitada = true;
            tablero[i][j].numpos=nummov;
            return true;

        }

        if (i<N && i>=0 && j<N && j>=0){
            nummov ++;
            tablero[i][j].numpos=nummov;
            tablero[i][j].visitada = true;
            c=resolver(i+(tablero[i][j].salto),j);
            d=resolver(i-(tablero[i][j].salto),j);
            e=resolver(i,j+(tablero[i][j].salto));
            f=resolver(i,j-(tablero[i][j].salto));

            if(c||d||e||f){
                    cout<<"hola"<<endl;
                return true;
            }

            else{
                tablero[i][j].numpos=-1;
                return false;
            }

        }
    }
		//TODO

	// imprime el tablero, con la info del salto y nummov de cada casilla
    void print()
    {
        for (int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(tablero[i][j].numpos != -1){
                cout<<tablero[i][j].salto<<" ("<<tablero[i][j].numpos<<")"<<'\t';
                }
                else
                     cout<<tablero[i][j].salto<<'\t';

            }
            cout<<endl;
        }
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

