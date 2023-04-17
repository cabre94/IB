#include <iostream>
#include <cmath>

using namespace std;

struct Punto3D_t{
	double x, y, z;

	void initialize(){
		cout << "Ingresar coordenada x: " << endl;
		cin >> x;
		cout << "Ingresar coordenada y: " << endl;
		cin >> y;
		cout << "Ingresar coordenada z: " << endl;
		cin >> z;
	}

};


double distance(Punto3D_t p1, Punto3D_t p2){
	double dist = 0;

	dist += ((p1.x-p2.x)*(p1.x-p2.x));
	dist += ((p1.y-p2.y)*(p1.y-p2.y));
	dist += ((p1.z-p2.z)*(p1.z-p2.z));

	return sqrt(dist);
}

int main(){

	Punto3D_t p1, p2;

	cout << "Ingresar datos del primer punto: " << endl;
	p1.initialize();

	cout << "Ingresar datos del segundo punto: " << endl;
	p2.initialize();

	cout << "La distancia entre los dos puntos es: " << distance(p1, p2) << endl;

	return 0;
}

// Con amor, Cabre.