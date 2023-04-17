#include  <iostream>

using namespace std;

template<class T1, class T2, class T3>
class CoordenadaCartesiana3D{
	T1 x;
	T2 y;
	T3 z;
public:
	CoordenadaCartesiana3D(T1 x_, T2 y_, T3 z_) : x(x_), y(y_), z(z_) {};
	void print(){
		cout << "x = " << x << endl;
		cout << "y = " << y << endl;
		cout << "z = " << z << endl;
	}
};


int main(){

	CoordenadaCartesiana3D<int, double, char> X{3, 1e-6, 97};

	X.print();

	return 0;
}