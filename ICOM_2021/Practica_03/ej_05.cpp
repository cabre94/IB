#include <iostream>

using namespace std;

int main(){
	char c;

	while( (c = cin.get()) != EOF){
		if( (c >= 'a') && (c <= 'z') )
			c = c - 'a' + 'A';
		cout.put(c);
	}

	return 0;
}

/*
Fijate que los caracteres en definitiva tienen asignado un numero que los
identifica en la tabla ASCII. Esto hace que puedas hacer operaciones como
comparar un caracter c con el caracter 'a' y con eso sabes si el caracter c
esta antes o despues que la 'a'. NO hace falta saber el numero correspondiente
a la 'a' en la tabla, vos te olvidas de eso, lo comparas con 'a' y fue.

En la tabla ASCII (y muchas otras) las letras en minusculas estan "seguidas"
con lo cual para saber si un caracter es una letra en minuscula alcanza con ver
si esta entre la 'a' y la 'z'.

OJO que 'a' y 'A' tienen valores diferentes. La diferencia entre 'a' y 'A' en la
tabla es la misma que la diferencia entre 'b' y 'B', que es la misma que 'c' y
'C' etc, asi que se puede usar esto para pasar de minuscula a mayuscula una
letra y viceversa.
*/

// Con amor, Cabre.