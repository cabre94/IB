#include <iostream>

using namespace std;
// Una de dos, o no entendi el enunciado o el resultado que dan como ejemplo
// esta mal. Yo lo que entendi es que dada una palabra, hay que recorrerla
// letra a letra. Cada una tiene un valor entero en la tabla ASCII, si es vocal
// hay que multiplicar por 2 y si es consonante por 4. Ademas, hay que
// multiplicar esto por el valor de la posicion de la letra y sumar el resultado
// para todas las letras. Si es asi, el resultado al ingresar la palabra
// "balseiro" es 11154 y no 12228 como dice el enunciado.

int main(){
	string s;
	int res = 0, i = 1;	// i es el peso de la letra

	cout << "Escribir alguna palabra:\n";
	cin >> s;
	
	for(char c : s){
		if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
			res += c*2*i;
		else
			res += c*4*i;
		i++;
	}
	
	cout << "El resultado es: " << res << ".\n";
    
	return 0;
}

// Con amor, Cabre.