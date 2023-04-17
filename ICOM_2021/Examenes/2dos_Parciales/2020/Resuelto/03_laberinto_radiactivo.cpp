#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <array>
#include <vector>
#include <algorithm>
#include <cassert>
#include <ctime>

using namespace std;




// caracteres en el mapa (el nombre de la variable indica su significado)
const char bunker = 'B';
const char bunkerVisitado='b';
const char salida='S';
const char pared='#';
const char espacio=' ';
const char espacioVisitado='o';
const char espacioResaltado='*';

// estructura para representar una celda del mapa {fila, columna}
struct Celda{
    // fila f y columna c de la celda
    size_t f,c;
};

// UDT para representar la instalacion (su mapa y sus niveles de radiacion)
class LaberintoRadiactivo{
public:
    // UDT que representa un camino de salida:
    struct Camino{
        // constructor default
        Camino() : radTotal(0.0) {}
        //destructor
        ~Camino() {}
        // agrega la celda cel al camino y suma la radiacion rad al total acumulado
        void agregarCelda(Celda cel, float rad){
			path.push_back(cel);
			radTotal += rad;
		}
        // vector de celdas que componen el camino
        vector<Celda> path;
        // radiacion total acumulada a lo largo del camino
        float radTotal;
    };
    // construye el LaberintoRadiactivo usando el archivo mapa_file que contiene el mapa en representacion ASCII
    // y radlevel_file que contiene 3 valores por cada linea: fila, columna y radiacion
    LaberintoRadiactivo(string mapa_file, string radlevel_file){
		string line;
		
		fstream file_map(mapa_file);
		if(file_map.is_open()){
			while(getline(cin, line)){
				mapa.push_back(line);
			}
			file_map.close();
		}else{
			throw string("Fallo al abrir el archivo" + mapa_file);
		}

		// Guardo las dimensiones
		nf = mapa.size();
		nc = mapa[0].size();	// Esta implicito que es rectangular, pero se puede chequear

		// Ahora hay que armar el mapa de radiaciones
		int f, c, r;
		rad.resize(nf);
		for(size_t i=0; i < nf; i++)
			rad[i].resize(nc);

		fstream rad_map(radlevel_file);
		if(file_map.is_open()){
			while(cin >> f >> c >> r){
				rad[f][c] = r;
			}
			file_map.close();
		}else{
			throw string("Fallo al abrir el archivo" + radlevel_file);
		}
	}
    // imprime el mapa en su estado actual
    void print(){
		for(size_t i=0; i < mapa.size(); i++){
			cout << mapa[i] << endl;
		}
	}
    // encuentra el mejor camino y lo resalta en el mapa
    // imprime el mapa y la radiacionTotal
    void resolver(); // TODO
private:
    // localiza la celda donde se encuentra el caracter c y la retorna
    Celda localiza(char c){
		for(size_t i=0; i < nf; i++){
			for(size_t j=0; j < nc; j++){
				if(mapa[i][j] == c)
					return Celda{i, j};
			}
		}
		throw string("No se encontro el caracter");
	}
    // recorre el laberinto recursivamente desde la Celda cel buscando la salida.
    // no se permite moverse en diagonal.
    // Si no encuentra la salida retorna nullptr.
    // Si la encuentra retorna un puntero al camino que conduce a la salida
    // minimizando la radiacion total. El camino se va armando en el mismo proceso recursivo.
    // Ayuda1: hay que buscar a partir de cada vecino, porque hay mas de un camino posible y nada garantiza que el primero que se encuentre sea el mejor
    // Ayuda2: hay que seleccionar y retornar el camino que tenga la minima radiacion total (y que va a hacer con los otros?)
    // Ayuda3: hay que desmarcar la casilla (ponerla como no visitada), antes de retornar, porque puede ser visitada nuevamente por otro camino.
    Camino* buscarMejorCamino(Celda cel); //TODO
    // dimensiones del mapa nf=numero de filas, nc=numero de columnas
    size_t nf, nc;
    // mapa de la instalacion en representacion de caracteres, cada fila es un string y cada caracter dentro de ese string es una celda
    // se puede ver como una matriz
    vector<string>mapa;
    // valores de radiacion residual rad[i][j] para cada celda {i,j}
    vector<vector<float>> rad;
};

int main(){

    try{
        LaberintoRadiactivo labrad("mapa.txt","niveles_radiacion.txt");
        labrad.print();
        labrad.resolver();
        return 0;
    }catch (string &s){
        cerr<< "Error: " << s << endl;
        return -1;
    }catch(...){
        cerr << "Error inesperado"<< endl;
        return -1;
    }
}
