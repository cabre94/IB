#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

/* Segun la the big three rule, si hacemos un defstructor y un copy constructor,
tambien hay que hacer un operador de asignacion (el operator=). Pero queda para
mas adelante. */

class SimMatrix{
public:
	SimMatrix(size_t dim_); 			// define una matriz de dim x dim
	SimMatrix(const SimMatrix &);		// copy-constructor
	~SimMatrix();

	void setElement(int i, int j, double val);
	double getElement(int i, int j) const;
	size_t getDim() const {return dim;};

	void print();
private:
	vector<double> *values;
	size_t dim;
};

int main(){
	srand(time(0));

	int n = 5, value = 1;
	SimMatrix m(n);

	for(int i=0; i < n; i++){
		for(int j=0; j <= i; j++){
			m.setElement(i, j, value);
			value++;
		}
	}

	cout << "Imprimo la matriz\n\n";
	m.print();

	cout << "\nAhora imprimo la copia\n\n";
	SimMatrix m2 = m;
	m2.print();
	
	return 0;
}

SimMatrix::SimMatrix(size_t dim_){
	dim = dim_;
	// Allocamos memoria para dim vectores, cada uno va a representar una fila
	values = new vector<double> [dim];

	// Para cada vector tenemos que hacer un resize adecuado. Como la matrix
	// es simetrica, para la primer fila nos alcanza con un numero, la segunda
	// con dos etc. y asi nos queda la triangular superior.
	for(size_t i=0; i < dim; i++)
		values[i].resize(i+1);
}

/* En el copy constructor tenemos que allocar memoria nueva en donde vamos a ir
copiando todos los elementos de la correspondiente matriz. Si NO allocamos
memoria nueva y copiamos el puntero tal cual, los dos punteros "values" (o sea,
el values y el m.values) van a apuntar a la misma direccion de memoria.
Despues, en el destructor, cuando liberamos la memoria y hacemos delete en uno
de los punteros, indirectamente estamos destruyendo la otra matriz.
No liberar la memoria en el constructor esta MAL.
*/
SimMatrix::SimMatrix(const SimMatrix &m){
	dim = m.getDim();	// Copiamos la dimension
	// Allocamos memoria
	values = new vector<double> [dim];

	// Ahora nos tenemos que copiar lo que haya en los vectores que representan
	// una fila. Una forma puede ser hacer lo que esta comentado
	/*for(size_t i = 0; i < dim; i++)
		values[i].resize(i+1);
	
	for(size_t i = 0; i < dim; i++){
		for(size_t j = 0; j <= i; j++)
			setElement(i, j, m.getElement(i, j));
	}*/

	// Pero una forma mas directa es copiar vector a vector
	for(size_t i = 0; i < dim; i++){
		values[i] = m.values[i];
	}
	/* Los std::vector, como estan bien hechos (muy bien hechos), permiten copiar
	las cosas directamente. Cuando vos haces unvector = otrovector, hace el resize,
	copia los elementos y todo lo necesario para que queden identicos.*/
}

SimMatrix::~SimMatrix(){
	/*Liberamos la memoria allocada en values, como pedimos memoria para varios
	vectores, hay que usar el []*/
	delete [] values;
}

void SimMatrix::setElement(int i, int j, double val){
	if(j > i)
		setElement(j,i,val);
	else
		values[i][j] = val;
}

double SimMatrix::getElement(int i, int j) const{
	if(j > i)
		return getElement(j,i);
	else
		return values[i][j];
}

void SimMatrix::print(){
	for(size_t i = 0; i < dim; i++){
		for(size_t j = 0; j < dim; j++)
			cout << getElement(i,j) << '\t';
		cout << endl;
	}
}

/*
Para mi este ejercicio tiene mas sentido y se aprende mas si se usa un double*
o un double**. Tambien se puede usar un vector (en lugar de un vector*) pero
ahi pierde sentido el copy-constructor que es lo que hay que practicar en esta
practica.
*/

// Con amor, Cabre.