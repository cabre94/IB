#include "icom_helpers.h"

struct Punto2D{
	double X;
	double Y;
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

int main(){
	Punto2D a = {0,0};
	Punto2D b = {0,3};
	Punto2D c = {4,0};
	Punto2D d = {4,3};

	vector<Punto2D> v{a,b,c,d};

	Poligono pol(v);

	cout << "Perimetro = " << pol.perimetro() << endl;
	cout << "Area = " <<  pol.area() << endl;

	Poligono pol2 = pol;

	cout << "Perimetro = " << pol2.perimetro() << endl;
	cout << "Area = " <<  pol2.area() << endl;

	return 0;
}

Poligono::Poligono(const vector<Punto2D> &v){
	vertices = v;
}

double Poligono::perimetro(){
	double res = Dist( vertices[0] , vertices[vertices.size()-1] );
	for(int i=0; i < vertices.size()-1; i++)
		res += Dist( vertices[i] , vertices[i+1] );
	return res;
}

double Poligono::area(){
	double res = 0;
	for(int i=1; i < vertices.size()-1; i++)
		res += Heron( vertices[0] , vertices[i] , vertices[i+1]);
	return res;
}

double Poligono::Heron( Punto2D a, Punto2D b , Punto2D c){
	double AB = Dist(a,b), BC = Dist(b,c), CA = Dist(c,a);
	double s = (AB + BC + CA) / 2;
	return sqrt(s * (s - AB) * (s - BC) * (s - CA));
}

double Poligono::Dist(Punto2D a, Punto2D b){
	return sqrt((a.X-b.X)*(a.X-b.X) + (a.Y-b.Y)*(a.Y-b.Y));
}

// Con amor, Cabre.