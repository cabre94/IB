#include <iostream>

using namespace std;

// Esto ya esta aspero
// n es la cantidad de palitos que hay en from. to es a donde necesitamos mover
// todo lo de from y aux es el palito del orto para auxiliarnos e ir acomodando.
// El caso base: Cuando tenes solo un disco en from, lo moves a to y fue. Fijate
// que como la funcion retorna void, para cortar la recursion tenes que meter
// un return sin nada, si no la funcion sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue y sigue bueno creo que se entendio
// La recursion, como verga explico esto. Presta atencion como hay que ir
// cambiando que palitos son from, to y aux.
// Tenes n discos en from.
// -
// Lo primero es sacarte los n-1 que estan arriba y dejarlos en aux, para que
// to quede libre y puedas mover el que quedo en from a aux.
// Entonces lo primero es mover n-1 discos DE FROM A AUX -> hanoi(n-1, from, aux, to)
// -
// Ahora te quedo 1 en from, n-1 en aux y to esta vacio, asi que moves 1 de from
// a to y listo -> hanoi( 1 , from, to, aux)
// -
// Ahora hay que volver a poner los n-1 que estan en aux y ponerlos en to.
// hanoi(n-1, aux, to, from)
// Y listo, quedaron n discos en to como queriamos.
// ¿ Como hicieron las llamadas hanoi(n-1, from, aux, to), hanoi( 1 , from, to, aux) y
// hanoi(n-1, aux, to, from) para hacer todo bien? no importa, pensa bien el caso
// base y asumi que la recursion hace las cosas bien, y deberia salir.
void hanoi(int n, int from, int to, int aux){
	if(n == 1) {
		cout << "Mover de " << from << " a " << to << endl;
		return;
	}
	hanoi(n-1, from, aux, to);
	hanoi( 1 , from, to, aux);
	hanoi(n-1, aux, to, from);
}

unsigned long long int mov(int n, int from, int to, int aux){
	if(n == 1)
		return 1;
	else
		return  mov(n-1,from,aux,to) + mov(1,from,to,aux) + mov(n-1,aux,to,from);
}

int main() {
	hanoi(5, 1, 3, 2);

	cout << endl << "# de discos\tTiempo [s]" << endl;
	for(int i=9; i <= 39; i+=10){
		cout << i << "\t" << mov(i,1,3,2)/(1000000.0) << endl;
	}
	
	return 0;
}

// Con amor, Cabre.