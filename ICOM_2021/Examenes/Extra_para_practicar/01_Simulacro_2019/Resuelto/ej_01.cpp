#include <iostream>
#include <string>

using namespace std;

/*
Voy a asumir que los strings que se ingresan son gramaticalmente correctos.
O sea, si por ejemplo ingreso "hola.como" no se si considerar "como" como una palabra nueva o no,
asi que directamente no me encargo de eso.
Entonces considero como una nueva palabra solo despues de un espacio o un '(' (creo que no me 
estoy comiendo ningun caso)
*/

// Pasa a minuscula un char
char lowercase(char c){
	if(c>='A' && c<='Z')
		return c - 'A' + 'a';
	return c;
}

// Pasa a mayuscula un char
char uppercase(char c){
	if(c>='a' && c<='z')
		return c - 'a' + 'A';
	return c;
}

void CapitalizeFirst(std::string &phrase){
	bool newWord = true;	// Para saber si tenemos una palabra nueva
	
	for(int i=0; i<phrase.size(); ++i){
		if(phrase[i] == ' ' || phrase[i] == '(')	// Si es un ' ' o '(', cambiamos newWord para indicar que vamos a tener una palabra nueva
			newWord = true;
		else if(newWord){	// Si tenemos una nueva palabra, ponemos el caracter en mayucula
			phrase[i] = uppercase(phrase[i]);
			newWord = false;
		}else{				// Si no, lo ponemos en minuscula
			phrase[i] = lowercase(phrase[i]);
		}
	}
}

int main(){

	string str = "este es el primer parcial de introduccion al computo";

	CapitalizeFirst(str);

	cout << str << endl;

	return 0;
}