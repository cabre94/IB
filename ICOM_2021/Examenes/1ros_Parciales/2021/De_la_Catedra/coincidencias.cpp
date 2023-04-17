#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

class Mazo
{
public:
  // Construye una instancia de Mazo leyendo las 'cartas' a partir la
  // informacion leida en el archivo 'mazo.txt'.
  // El archivo cuenta con un string por renglon, con los simbolos de la
  // carta
  Mazo(const string &fname); // TODO

  // Metodo que verifica que todo par de cartas del mazo tenga un solo
  // elemento en comun.
  bool esValido(); //TODO

  //Funcion que imprime el mazo
  void print(); //TODO

private:
  // representacion de todas las cartas
  vector<string> cartas;

  // Metodo que retorna la cantidad de simbolos comunes entre las cartas
  // en las posiciones i y j
  unsigned int coincidencias(int i, int j); //TODO

  //Funcion auxiliar que calcula el numero de ocurrencias del
  //caracter c en el string s1
  int encontrar_car(const string &s1, char c)
  {
    int ocurrencias = 0;
    for (int i = 0; i < s1.size(); i++)
    {
      if (c == s1[i])
        ocurrencias++;
    }
    return ocurrencias;
  }
};

Mazo::Mazo(const string &fname)
{ // TODO
  ifstream ifile(fname);
  string aux;
  if (ifile)
  {
    while (ifile >> aux)
      cartas.push_back(aux);
  }
  else
    cout << "Archivo no encontrado" << endl;
  ifile.close();
}

bool Mazo::esValido()
{ // TODO
  if (cartas.size())
  { //Si cartas es no vacio
    for (int i = 0; i < cartas.size(); i++)
    {
      //Chequeo integridad de cada carta:
      if (coincidencias(i, i) != cartas[i].size())
        return false;
      //Comparo con las demás:
      for (int j = i + 1; j < cartas.size(); j++)
      {
        if (coincidencias(i, j) != 1)
        {
          cout << coincidencias(i, j) << " en: " << i << ", " << j;
          cout << endl;
          return false;
        }
      }
    }
  }
  else
  {
    cout << "No hay cartas en el mazo." << endl;
    return false;
  }

  return true;
}

void Mazo::print()
{ // TODO
  if (cartas.size())
  {
    for (int i = 0; i < cartas.size(); i++)
      cout << i << ": " << cartas[i] << endl;
  }
  else
    cout << "Mazo vacío" << endl;
}

unsigned int Mazo::coincidencias(int i, int j)
{ // TODO
  //Chequeo que los  indices
  //estén dentro del tamaño del arreglo:
  assert(i < cartas.size() || j < cartas.size());
  string si = cartas[i], sj = cartas[j];
  // Chequeo que las cartas tengan mismo
  //numero de figuras:
  assert(si.size() == sj.size());
  int num_fig = si.size(), ocur = 0;
  for (int k = 0; k < num_fig; k++)
    ocur += encontrar_car(sj, si[k]);

  return ocur;
}

int main()
{
  Mazo m("mazo.txt");
  m.print();
  cout << "el mazo es " << (m.esValido() ? "VALIDO" : "INVALIDO")
       << endl;

  return 0;
}
