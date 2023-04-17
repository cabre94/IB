#include <iostream>
#include <string>
#include <vector>
#include <cassert>


using namespace std;

// Chequea si un caracter es una vocal
bool vocal(char c){
	if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
		return true;
	else if(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
		return true;
	else
		return false;
}

// Pasa a minucula un char
char lowercase(char c){
	if(c>='A' && c<='Z')
		return c - 'A' + 'a';
    return c;
}

// Chequea si un caracter es una letra
bool esLetra(char c){
	if((c>='A' && c<='Z') || (c>='a' && c<='z'))
		return true;
	else
		return false;
}

/* Funcion para chequear que la 'y' esta sola (en español). No se si este nivel de detalle
 haga falta para el parcial. Hay muchos casos verga */
bool ySolaEnEsp(const string &s, int i){
	if(i == 0 || !esLetra(s[i-1])){	// Si a la izquierda no hay una letra 
		if(i == (s.size()-1) || !esLetra(s[i+1])) // Y a la derecha tampoco
			return true;
	}
	return false;
		
}

/* Funcion para chequear que la 'y' esta sola (en jeringozo) */
bool ySolaEnJer(const string &s, int i){
	if(i == 0 || !esLetra(s[i-1])){	// Si a la izquierda no hay una letra
		if(i < (s.size()-2) && s[i+1] == 'p' && s[i+2] == 'i') // Y a la derecha hay un 'pi'
			return true;
	}
	return false;
}// No se si hay alguna palabra "posta" que empiece con 'ypi'. En ese caso la funcion falla, pero no jodamos.

string esp2jeringozo(const string &s){
	string res;

	for(int i=0; i < s.size(); i++){
		if(vocal(s[i])){
			res.push_back(s[i]);
			res.push_back('p');
			res.push_back(lowercase(s[i]));
		}else if(s[i] == 'y' || s[i] == 'Y'){
			if( ySolaEnEsp(s, i) ){	// Chequear que la 'y' esta sola
				res.push_back(s[i]);
				res.push_back('p');
				res.push_back('i');
			}else{		//	Si no esta sola, solo agrego la 'y'
				res.push_back(s[i]);
			}
		}else{
			res.push_back(s[i]);
		}
	}

	return res;
}

string jeringozo2esp(const string &s){
	string res;

	for(int i=0; i < s.size(); i++){
		if(vocal(s[i])){
			res.push_back(s[i]);
			i += 2;
		}else if(s[i] == 'y' || s[i] == 'Y'){
			if( ySolaEnJer(s, i) ){
				res.push_back(s[i]);
				i += 2;
			}else{
				res.push_back(s[i]);
			}
		}else{
			res.push_back(s[i]);
		}
	}

	assert(s == esp2jeringozo(res));	// Esto para chequear rapido si la funcion tiene algun error (pero que pase no quiere decir que no haya otros errores)

	return res;
}

int main(){

	string str1 = "Hola, ¿como estas?";
	string str2 = "Bien, ¿y vos?";

	vector<string> frases = {
		"Hola, ¿como estas?",
		"Bien, ¿y vos?",
		"Yo tambien estoy, ¿y vos?",
		"y",
		"Y, ¡eramos tan pobres!"
	};

	for(int i=0; i < frases.size(); i++){
		string jer = esp2jeringozo(frases[i]);
		string esp = jeringozo2esp(jer);
		
		cout << frases[i] << " --> ";
		cout << jer << " --> ";
		cout << esp << endl;
	}


	return 0;
}