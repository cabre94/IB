#include <iostream>

using namespace std;

// Reemplaza el caracter viejo por el nuevo en el string nativo s
void Replace(char s[], char nuevo, char viejo);

int main(){
	char s[64] = "aeiouuoiea";
	char nuevo = 'u', viejo = 'o';

	cout << s << endl;
	Replace(s, nuevo, viejo);
	cout << s << endl;

	return 0;
}

// Reemplaza el caracter viejo por el nuevo en el string nativo s
void Replace(char s[], char nuevo, char viejo){
	int i=0;

	while(s[i]){
		if(s[i] == viejo)
			s[i] = nuevo;
		i++;
	}
}

/*
El array nativos de caracteres tiene un 0 al final como convencion. Por eso
lo podemos usar como condicion del while, ya que cualquier cosa distinta de 0
se considera true y solo el 0 (o equivalentes) false.
*/

// Con amor, Cabre.