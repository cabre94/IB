/*
date: 20-10-21
File: 05_en_campaña.cpp
Author : Facundo Martin Cabrera
Email: cabre94@hotmail.com facundo.cabrera@ib.edu.ar
GitHub: https://github.com/cabre94
GitLab: https://gitlab.com/cabre94
Description: 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Esta función eliminará los espacios extras contenidos en el string que
// recibe como argumento.
void elimina_espacios_redundantes(string& discurso){
	// Esto me convierte en un stream como cuando se usa el cin o se lee un
	// file. Asi es una manera muy comoda de leer palabra a palabra.
	// Lo logico seria hacerlo al leer el txt en el main, pero nos piden estas
	// funciones y hay que respetar el prototipo
	istringstream iss(discurso);

	string word;
	discurso.clear(); // Limpiamos el discurso (iss tiene una copia)
	
	while(iss >> word)
		discurso.append(word+" "); // Agrego word con solo un espacio
	discurso.pop_back(); // Saco el ultimo espacio que puse demas
}

//Esta elimina las palabras repetidas, dejando sólo una de ellas
// (“el el” => “el”) en el texto que se le pasa como argumento.
void elimina_palabras_repetidas(string & discurso){
	// Esto me convierte en un stream como cuando se usa el cin o se lee un
	// file. Asi es una manera muy comoda de leer palabra a palabra.
	// Lo logico seria hacerlo al leer el txt en el main, pero nos piden estas
	// funciones y hay que respetar el prototipo
	istringstream iss(discurso);
	// Segun el enunciado, las palabras repetidas son cosas del estilo
	// "el el", asi que no me voy a meter en caso de que una tenga una 
	// mayuscula como "El el" o si hay un punto/coma/etc como "el el."
	string word, last_word;
	discurso.clear(); // Limpiamos el discurso (iss tiene una copia)

	while(iss >> word){
		if(word != last_word)
			discurso.append(word+" ");
		last_word = word;
	}
	discurso.pop_back(); // Saco el ultimo espacio que puse demas	
}

int main(){

	string discurso, linea;

	ifstream file("discurso.txt");
	if(file.is_open()){
		while(getline(file, linea))
			discurso += linea;
        file.close();
    }

	cout << discurso << endl;

	elimina_espacios_redundantes(discurso);
	cout << endl << discurso << endl;

	elimina_palabras_repetidas(discurso);
	cout << endl << discurso << endl;


	return 0;
}