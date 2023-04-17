#include <iostream>
#include <cmath>
#include <array>
#include <algorithm>
#include <ctime>

using namespace std;

struct Terna{
    int i, j, value;

    bool operator<(const Terna &t2) const{return value < t2.value;}
    double norm() const{return sqrt(i*i+j*j);}
};

bool cmp1(const Terna &t1 ,const Terna &t2){
    return t1.norm() < t2.norm();
}

int main(){
	srand(time(0));

    array<Terna,4> v;
	int size = sizeof(v) / sizeof(Terna);

	cout << "i\tj\tValue" << endl;
	// Inicializo todas las ternas con valores random
	for(int k=0; k < size; k++){
		v[k].i = rand() % 100;
		v[k].j = rand() % 100;
		v[k].value = rand() % 1000;
		cout << v[k].i << "\t" << v[k].j << "\t" << v[k].value << endl;
	}

	
	cout << "\n\nDespues de ordenarlos segun el atributo 'value':\n";
	sort(v.begin(), v.end());

	cout << "i\tj\tValue" << endl;
	for(int k=0; k < size; k++)
		cout << v[k].i << "\t" << v[k].j << "\t" << v[k].value << endl;


	cout << "\n\nDespues de ordenarlos segun la distancia entre i y j:\n";
	sort(v.begin(), v.end(), cmp1);

	cout << "i\tj\tValue\tDistancia" << endl;
	for(int k=0; k < size; k++){
		cout << v[k].i << "\t" << v[k].j << "\t" << v[k].value << '\t' << v[k].norm() << endl;
	}

	cout << "\nAhora los ordeno segun la distancia entre i y j pero de mayor a menor:\n";
	sort(v.rbegin(), v.rend(), cmp1);

	cout << "i\tj\tValue\tDistancia" << endl;
	for(int k=0; k < size; k++){
		cout << v[k].i << "\t" << v[k].j << "\t" << v[k].value << '\t' << v[k].norm() << endl;
	}

    return 0;
}

// Con amor, Cabre.