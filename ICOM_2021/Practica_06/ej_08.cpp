#include <iostream>

using namespace std;

// Función StrStr que reciba dos strings de <string> y busque sobre el primero de ellos por la ocurrencia del segundo.
// tiene que devolver la ṕosicion de s1 donde aparece s2, si no aparece hay que devoler un -1.
int StrStr(string s1, string s2){
	return s1.find(s2);
}

// https://www.cplusplus.com/reference/string/string/
// s1.length() : devuelve el largo/longitud del string
// s.begin() : creo que devuleve el puntero al principio del string
// s.end() : lo mismo pero para el final
// s.find(s2) : busca el string s2 en el s1. Si lo encuentra, devuelve la posicion del elemento de s donde arranca la coincidencia.
// si no lo encuentra, devuelve string::npos. Esto es solamente un numero que denota que no se encontro, no importa. 
// s.find(s2,pos+1) : Tambien se le puede mandar un segundo argumento para indicar desde que posicion arrarcar a buscar. Si no se le pasa
// nada, por default este valor es cero, o sea que va a bucar desde el arranque y va a devolver la primer coinncidencia.
// En general cuando se quiera guardar el retorno de s.find(lo que sea), hay que usar el tipo de variable size_t, que es un tipo que puede 
// guardar cualquier tamaño. O sea, la linea de codigo deberia ser: size_t pos = s.find(s2); y ahi la variable pos tiene la posicion en
// donde se encontro s2.
// s.replace(s.find(s2), s2.length(), "eternos"): Es una funcion que reemplaza un pedazo del string s por otro string nuevo. Para esto 
// hay que pasarle la posicion de s donde arrancar a cambiar ( s.find(s2) ), cuantos caracteres se quieren cambiar/sacar ( s2.length() ) y
// cual es el string nuevo que se quiere meter.


int main(){
	string a("JUAN ESTA CASADO CON MARIA");
	string b = "ASADO";
	string c{"ABCDE"};
	string d = "BCE";

	cout << StrStr(a,b) << endl;
	cout << StrStr(c,d) << endl;

	return 0;
}

// Con amor, Cabre.