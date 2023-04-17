#include <iostream>

using namespace std;

struct A{
	int val;
	A(){
		val = 0;
		cout << "A default: " << this << '\t' << val << endl;
	}
	A(int v){
		val = v;
		cout << "A con argumento: " << this << '\t' << val << endl;
	}
	~A(){
		cout << "~A: " << this << '\t' << val << endl;
	}
};



int main(){
	A *pa = new A(10);		// Aca el 10 es el argumento que se pasa al constructor
	A *pb = new A[10];		// Mientras que aca es para allocar 10 elementos de tipo A

	// destruccion de pa y pb
	delete pa;
	delete [] pb;

	// A *pc = new A[10000000000000];		// Tira el error bad_alloc
	// delete [] pc;

	return 0;
}

// Con amor, Cabre.