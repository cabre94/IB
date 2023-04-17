#include <iostream>

using namespace std;

void a(){

	unsigned int color;
	int R, G, B;

	cout << "Ingrese la componente R del color (0-255):" << endl;
	cin >> R;
	cout << "Ingrese la componente G del color (0-255):" << endl;
	cin >> G;
	cout << "Ingrese la componente B del color (0-255):" << endl;
	cin >> B;

	color = R + (B<<8) + (G<<16);

	cout << "El color ingresado es: " << color << endl;

}

void b(){
	unsigned int color;
	int R, G, B;

	cout << "Ingrese color:\n";
	cin >> color;

	if(color < 0 || color > 0xffffff){
		cout << "Color invalido" << endl;
		return;
	}else{
		R = color % 256;		// Comentario al final
		G = (color >> 8) % 256;
		B = (color >> 16);
	}

	cout << "Las componentes en RGB son:" << endl;
	cout << "R: " << R << endl;
	cout << "G: " << G << endl;
	cout << "B: " << B << endl;
}


int main(){

	a();

	b();

	return 0;
}

/*
- color % 256 te da un numero entre 0 y 255
- Aca te tenes que quedar viendo el ejercicio hasta que te des cuenta que hacer
color % 256 te deja los ultimos 8 bits del numero que hayas ingresado (2^8 = 256)
- Entonces en definitiva color % 256 te da la componente R, que son los 8 bits
menos significativos.
- Despues con color >> 8 corres todos los bits a la derecha 8 lugares. o sea, 
que los 8 bits del R lo volaste y ahora los 8 bits que quedaron como menos
significativos son los del G y para obtenerlos haces % 256.
- Algo asi:
10101010 11111111 00000001 ---> 00000000 10101010 11111111
	B		 G		 R			  caca		B		 G			R

La inversa toma las componentes R, G, B y lo que haces es correrlo 0, 8 o 16
bits a la izquierda usando el operador >>
R = 00000001	-->	00000000 00000000 00000001
G = 11111111	--> 00000000 11111111 00000000
B = 10101010	--> 10101010 00000000 00000000
sumando			--> 10101010 11111111 00000001
*/

// Con amor, Cabre.