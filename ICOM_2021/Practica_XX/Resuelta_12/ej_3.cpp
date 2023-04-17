#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Punto2D{
	double X, Y;
	Punto2D operator-(Punto2D v){return Punto2D{X - v.X, Y - v.Y};}
	double norm(){return sqrt(X*X + Y*Y);}
};

struct Poligono {
public:
	Poligono(const vector<Punto2D> &vertices);			// construye un poligono cerrado con los vertices dados
	double perimetro();				// retorna el perimetro del poligono
	double area();					// retorna el area del poligono
private:
	vector<Punto2D> vertices;
	// Formula de Heron para sacar el area de un triangulo
	// https://es.wikipedia.org/wiki/F%C3%B3rmula_de_Her%C3%B3n
	double Heron(Punto2D a, Punto2D b, Punto2D c);
	double Dist(Punto2D a, Punto2D b);
};

// Funcion para ver si se rompe todo cuando creamos y destruimos una copia de un Poligono
void check(Poligono pol){
	cout << "Perimetro = " << pol.perimetro() << endl;
	cout << "Area = " <<  pol.area() << endl;
}

int main(){
	Punto2D a = {0,0};
	Punto2D b = {0,3};
	Punto2D c = {4,0};
	Punto2D d = {4,3};

	vector<Punto2D> v{a,b,c,d};

	Poligono pol(v);

	cout << "Perimetro = " << pol.perimetro() << endl;
	cout << "Area = " <<  pol.area() << endl;

	check(pol);

	return 0;
}

Poligono::Poligono(const vector<Punto2D> &v){
	vertices = v;
	// cout << &vertices << " " << &v << endl;	// Para chequear que hace una copia del vector
}
// Poligono::Poligono(const vector<Punto2D> &v) : vertices(v){
// 	cout << &vertices << " " << &v << endl;	// Para chequear que hace una copia del vector
// }

double Poligono::perimetro(){
	double res = Dist( vertices[0] , vertices[vertices.size()-1] ); // Dist entre el primero y el ultimo vertice
	for(int i=0; i < vertices.size()-1; i++)
		res += Dist( vertices[i] , vertices[i+1] );
	return res;
}

// Divido al poligono en triangulitos con un vertice en comun y saco el area de cada uno
double Poligono::area(){
	double res = 0;

	for(int i=1; i < vertices.size()-1; i++)
		res += Heron( vertices[0] , vertices[i] , vertices[i+1]);
	return res;
}

double Poligono::Heron( Punto2D a, Punto2D b , Punto2D c){
	double AB = Dist(a,b), BC = Dist(b,c), CA = Dist(c,a);
	double s = (AB + BC + CA) / 2;

	return sqrt(s * (s - AB) * (s - BC) * (s - CA)); // https://es.wikipedia.org/wiki/F%C3%B3rmula_de_Her%C3%B3n
}

double Poligono::Dist(Punto2D a, Punto2D b){
	return (a-b).norm();
}
