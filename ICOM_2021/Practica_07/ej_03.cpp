#include <iostream>
#include <string>
#include <ctime>

using namespace std;


class myUDT{
public:
	myUDT(){cout << "Construyo " << this << endl;}
	~myUDT(){cout << "Destruyo " << this << endl;}
};

// Un "truquito" comun es crearse un tipo de dato que represente un error. Des-
// pues uno puede hacer un throw de ese struct/class que se creo 
// Si uno lo quiere hacer bien bien bien tendria que heredar std::exception
// e implementar ciertos metodos. Pero por ahora no lo sabemos y creo que tam
// poco se ve en la materia
struct myError{};


// Me arme esta funcion para que throwdee distintos tipos de excepciones
void funB(){
	myUDT udt_B;
	int x = rand()%4;
	// cout << x << endl;

	if(x == 0)
		throw 42;
	else if(x == 1)
		throw 42.0;
	else if(x == 2)
		// Los corchetes son necesarios porque hay que lanzar un objeto instanciado
		throw myError{};	
	else
		throw string("error");
}

void funA(){
	myUDT udt_A;
	funB();
}

int main(){
	srand(time(0));

	try{
		funA();
	}catch(int){
		cout << "Excepcion tipo int atrapada" << endl;
	}catch(double){
		cout << "Excepcion tipo double atrapada" << endl;
	}catch(myError){
		cout << "Excepcion tipo myError atrapada" << endl;
	}catch(...){
		cout << "Excepcion no especificada atrapada" << endl;
	}// No catcheamos string para que lo haga el catch(...)
	
	return 0;
}

// Con amor, Cabre.