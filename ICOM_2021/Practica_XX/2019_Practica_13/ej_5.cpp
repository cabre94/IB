#include "icom_helpers.h"

class Base{
private:
	double dato;
};

class Deriv: public Base{
	private:
		int otro_dato;
};

void f(Base b){
	cout << "En f, el tamaño es: " << sizeof(b) << endl;
}

int main(){
	Deriv kk;
	cout << "En el main, el tamaño es: " << sizeof(kk) << endl;
	f(kk);
	return 0;
}

// Con amor, Cabre.