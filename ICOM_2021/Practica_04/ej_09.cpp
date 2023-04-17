#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

/*
El temita de este ejercicio esta en que por los errores propios de usar puntos
flotantes, dos valores que en teoria deberian ser iguales, no lo son.
Ponele, un angulo deberia ser 90° y te termina dando 90° + alguna mierda chica.
Ahi cuando quieras ver si el triangulo es rectangulo, te va a dar que no.
Esto no siempre pasa igual, depende de los vertices que elijas.
Cuestion, para solventar lo que hacemos es definir una cota/tolerancia. Si la
diferencia entre dos numeros es menor que esa tolerancia, los vamos a considerar
iguales.
Obviamente esa tolerancia tiene que ser chica. Si no valores groseramente
distintos los vas a tomar iguales.
*/

// Estructura para representar un punto en el plano
struct Punto2D{
	double x;
	double y;
};

// Estructura para representar un triangulo
struct Triangulo{
public:
	enum ClaseLado {EQUILATERO, ISOCELES, ESCALENO};			// Tipos de triangulo segun sus lados
	enum ClaseAngulo {ACUTANGULO, RECTANGULO, OBTUSANGULO};		// Tipos de triangulo segun sus angulos

	ClaseLado clasificaPorLado();								// Devuelve el tipo de triangulo segun sus lados
	ClaseAngulo clasificaPorAngulo();							// Devuelve el tipo de triangulo segun sus angulos
	void cargaVertices();										// Carga los vertices del triangulo
	string imprimeTipoSegunLado();								// Imprime el tipo de triangulo segun sus lados
	string imprimeTipoSegunAngulo();							// Imprime el tipo de triangulo segun sus angulos

private:
	// Definimos una tolerancia para considerar a dos numeros iguales.
	// La definimos const porque no vamos a cambiarla ni queremos que cambie.
	const double TOL = 1e-7;

	Punto2D vertices[3];

	// Calcula el producto interno entre dos puntos
	double prodInterno(Punto2D p, Punto2D q){return p.x*q.x + p.y*q.y;}
	// Calcula la distancia al cuadrado entre dos puntos
	double normaCuadrado(Punto2D p, Punto2D q);
	// Calcula el coseno del angulo entre los segmento pq y pr
	double cosAngulo(Punto2D p, Punto2D q, Punto2D r);

	bool aprox_igual(double a, double b){return fabs(a-b) < TOL;}
};



int main(){
	Triangulo tr;
	
	tr.cargaVertices();

	cout << "El triangulo es " << tr.imprimeTipoSegunLado();
	cout << " y " << tr.imprimeTipoSegunAngulo() << endl;

	return 0;
}


// Devuelve el tipo de triangulo segun sus lados
Triangulo::ClaseLado Triangulo::clasificaPorLado(){
	double l1 = normaCuadrado(vertices[0],vertices[1]);
	double l2 = normaCuadrado(vertices[1],vertices[2]);
	double l3 = normaCuadrado(vertices[2],vertices[0]);

	/* Esto no estaria del todo bien
	if( (l1==l2) && (l2==l3))
		return EQUILATERO;
	else if( (l1==l2) || (l2==l3) || (l3==l1) )
		return ISOCELES;
	else
		return ESCALENO;*/

	if( aprox_igual(l1, l2) && aprox_igual(l2, l3))
		return EQUILATERO;
	else if(aprox_igual(l1, l2) || aprox_igual(l2, l3) || aprox_igual(l3, l1))
		return ISOCELES;
	else
		return ESCALENO;
}

// Devuelve el tipo de triangulo segun sus angulos
Triangulo::ClaseAngulo Triangulo::clasificaPorAngulo(){
	double alpha = cosAngulo(vertices[0],vertices[1],vertices[2]);
	double beta  = cosAngulo(vertices[1],vertices[2],vertices[0]);
	double gamma = cosAngulo(vertices[2],vertices[0],vertices[1]);

	/*Esto tampoco estaria del todo bien
	if( (alpha == 0) || (beta == 0) || (gamma == 0) )
		return RECTANGULO;
	else if( (alpha < 0) || (beta < 0) || (gamma < 0))
		return OBTUSANGULO;
	else
		return ACUTANGULO;*/
	
	if(aprox_igual(alpha,0) || aprox_igual(beta,0) || aprox_igual(gamma,0) )
		return RECTANGULO;
	else if( (alpha < 0) || (beta < 0) || (gamma < 0))
		return OBTUSANGULO;
	else
		return ACUTANGULO;
}

// Carga los vertices del triangulo
void Triangulo::cargaVertices(){
	for(int i=0; i < 3; i++){
		cout << "Coordenada x del vertice " << i+1 << ": " << endl;
		cin >> vertices[i].x;
		cout << "Coordenada y del vertice " << i+1 << ": " << endl;
		cin >> vertices[i].y;
	}
}

// Imprime el tipo de triangulo segun sus lados
string Triangulo::imprimeTipoSegunLado(){
	ClaseLado lados = clasificaPorLado();

	switch(lados){
		case EQUILATERO:
			return "EQUILATERO";
		case ISOCELES:
			return "ISOCELES";
		case ESCALENO:
			return "ESCALENO";
	}
	assert(0); // Nunca deberia llegar aca, el assert hace explotar el programa
}

// Imprime el tipo de triangulo segun sus angulos
string Triangulo::imprimeTipoSegunAngulo(){
	ClaseAngulo angulo = clasificaPorAngulo();

	switch(angulo){
		case ACUTANGULO:
			return "ACUTANGULO";
		case RECTANGULO:
			return "RECTANGULO";
		case OBTUSANGULO:
			return "OBTUSANGULO";
	}
	assert(0); // Nunca deberia llegar aca, el assert hace explotar el programa
}

// Calcula la distancia al cuadrado entre dos puntos
double Triangulo::normaCuadrado(Punto2D p, Punto2D q){
	Punto2D qp = {p.x-q.x , p.y-q.y};
	return prodInterno(qp,qp);
}

// Calcula el coseno del angulo entre los segmentos pq y pr
double Triangulo::cosAngulo(Punto2D p, Punto2D q, Punto2D r){
	Punto2D a = {q.x-p.x , q.y-p.y};
	Punto2D b = {r.x-p.x , r.y-p.y};

	double A = sqrt(prodInterno(a,a));
	double B = sqrt(prodInterno(b,b));

	// cout << A << " " << B << endl;

	double cos = prodInterno(a,b) / (A*B);

	return cos;
}

// Con amor, Cabre.