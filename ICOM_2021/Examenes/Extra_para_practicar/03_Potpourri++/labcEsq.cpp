#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// UDT para representar las coordenadas de una celda del laberinto
struct Celda
{
    int i; // fila
    int j; // columna
};

// UDT para representar el laberinto
struct Laberinto
{   
    // la representaci�n como vector de strings, permite usarla como matriz rep[i][j]
    vector<string> rep;

    // todos los caracteres que puede haber en el laberinto
    const char pared = '#';
    const char entrada = 'E';
    const char salida = 'S';
    const char espacio = ' ';
    const char entrada_visitada = 'e';
    const char salida_visitada = 's';
    const char espacio_visitado = 'o';

    // construye el laberinto leyendo desde el archivo cuyo nombre es el argumento
    Laberinto(const string &filename)
    {
        ifstream lab(filename);
        string s;
        while (!lab.eof())
        {
            getline(lab, s);
            rep.push_back(s);
        }
        lab.close();
    }

    // busca la celda que contiene el caracter c y la retorna
    // se usa para localizar la entrada del laberinto
    Celda buscar(char c)
    {
        Celda p;
        
        for(int i=0;i<rep.size();i++){
            size_t found = rep[i].find(c);
            if(found!=string::npos)
            {
                p.j=found;
                p.i=i;
                return p;
            }
        }

    }

    // imprime el laberinto
    void print()
    {
        for (int i = 0; i < rep.size(); i++)
        {   
            cout << rep[i] << endl;
        }
    }

    void resolver()
    {
        Celda ent = buscar(entrada);
        if (backtrack(ent))
        {
            print();
            cout << "Encontr� la solucion" << endl;
        }
        else
        {
            print();
            cout << "No hay solucion" << endl;
        }
    }

    // funcion recursiva que intenta encontrar la salida desde la celda cel
    // que se le pasa como argumento. A medida que avanza, va marcando los
    // celdas como visitadas. si por un camino no se llega a la salida, vuelve
    // a marcar la celda como no visitada y retorna falso.
    // si encuentra la salida retorna verdadero.
    bool backtrack(Celda cel)
    {
        Celda der = {cel.i, cel.j + 1};
        Celda izq = {cel.i, cel.j - 1};
        Celda arr = {cel.i - 1, cel.j};
        Celda aba = {cel.i + 1, cel.j};
        if (cel.i < 0 || cel.i >= rep.size() || cel.j < 0 || cel.j >= rep[0].size())
        {
			cout << 1 << endl;
            return false;
        }
        if (rep[cel.i][cel.j] == salida)
        {
			cout << 2 << endl;
            rep[cel.i][cel.j] = salida_visitada;
            return true;
        }
        if (rep[cel.i][cel.j] == pared || rep[cel.i][cel.j] == entrada_visitada)
        {
			cout << 3 << endl;
            return false;
        }
        if (rep[cel.i][cel.j] == espacio_visitado)
        {
			cout << 4 << endl;
            rep[cel.i][cel.j] = espacio;
            return false;
        }
        if (rep[cel.i][cel.j] == entrada)
        {
			cout << 5 << endl;
            rep[cel.i][cel.j] = entrada_visitada;
            backtrack(der);
        }
        if (rep[cel.i][cel.j] == espacio)
        {
			cout << 6 << " " << cel.i << " - " << cel.j << endl;
            rep[cel.i][cel.j] = espacio_visitado;
            backtrack(der);
            backtrack(izq);
            backtrack(arr);
            backtrack(aba);
            return false;
        }
    }
}
;

int main()
{
    Laberinto lab("laberinto.txt");
    //lab.print();
    lab.resolver();
    return 0;
}
