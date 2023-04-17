#include <iostream>

using namespace std;

/*
- En la recursion es importante tener bien claro el caso base, es decir, el caso
(o los casos) en donde ya no seguimos haciendo llamadas recursivamente.
En este ejercicio, el caso base es cuando el numero tiene un solo digito.
Cuando llegamos a ese punto, si es -7, 0 o 7 retornamos true, si no false.
- El otro punto importante en estos ejercicios es como hacer la recursividad.
No se si es el mejor consejo, pero esta parte cuanto mas la pensas, peor.
Si te pones a pensar en que la funcion llama a la otra, y la otra a la otra y
la otra a la otra y a la otra, te mareas.
Aca lo que te dicen es que si un numero es dividible por 7, entonces el numero
que se obtiene de restar dos veces las unidades al resto de cifras, tambien es
divisible por 7. Asi que calculo ese nuevo numero y hago la recursion. Despues
que hace esa llamada nueva no me importa.
*/

bool esDivisiblePor7(int nro){
	if((nro < 10) && (nro > -10)){
		if((nro==7) || (nro==0) || (nro==-7))
			return true;
		else
			return false;
	}else{
		int unidad = nro % 10;
		// Calculo el nuevo numero y pregunto si es divisible por 7
		return esDivisiblePor7(nro/10 - 2*unidad );
	}
}


int main(){
	int n;

	cout << "Ingresar un numero entero" << endl;
	cin >> n;

	if(esDivisiblePor7(n))
		cout << n << " es divisible por 7" << endl;
	else
		cout << n << " no es divisible por 7" << endl;
		
	return 0;
}

// Con amor, Cabre.