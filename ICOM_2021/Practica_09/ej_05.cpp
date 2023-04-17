#include <iostream>
#include <vector>
#include <cassert>
#include <ctime>

using namespace std;

// Me creo una UDT para lanzar una excepcion en caso de querer sumar dos
// matrices y no coincidan las dimensiones. Soy medio choto para elegir nombres
struct dimNotMacht{};

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

SimMatrix *sumaSimMatrix(const SimMatrix &m1, const SimMatrix &m2);


int main(){
	srand(time(0));

	int n = 3, value = 1;
	SimMatrix m1(n), m2(n);

	for(int i=0; i < n; i++){
		for(int j=0; j <= i; j++){
			m1.setElement(i, j, value);
			m2.setElement(i, j, n*n - value);
			value++;
		}
	}

	cout << "m1 = " << endl;
	m1.print();
	cout << "\nm2 = " << endl;
	m2.print();

	// cout << "\nAhora imprimo la copia\n\n";
	// SimMatrix m2 = m;
	// m2.print();

	cout << "\nSuma" << endl;
	SimMatrix *suma = sumaSimMatrix(m1, m2);
	suma->print();

	// No hay que olvidar de destruir el puntero que se construyo en
	// sumaSimMatrix y guardamos en suma
	delete suma;
	
	return 0;
}

SimMatrix::SimMatrix(size_t dim_){
	dim = dim_;
	values = new vector<double> [dim];

	for(size_t i=0; i < dim; i++)
		values[i].resize(i+1);
}

SimMatrix::SimMatrix(const SimMatrix &m){
	dim = m.getDim();
	values = new vector<double> [dim];

	for(size_t i = 0; i < dim; i++){
		values[i] = m.values[i];
	}
}

SimMatrix::~SimMatrix(){
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

/*Aca tenemos que retornar un puntero que contenga la suma.
Si nosotros creamos una variable local SimMatrix, ahi guardamos la suma y
despues retornamos su direccion de memoria, la cosa puede parecer que esta bien
pero no. Esa variable local se destruye cuando esta funcion termina, asi que
la direccion de memoria que retornamos apunta a mierda.
Lo que hay que hacer es allocar memoria para una SimMatrix, guardar ahi la suma
y retonar ese puntero. Asi, el contenido no se destruye al salir de la funcion
PERO tenemos que nosotros liberarla en algun momento haciendo delete*/
SimMatrix *sumaSimMatrix(const SimMatrix &m1, const SimMatrix &m2){
	if(m1.getDim() != m2.getDim())
		throw dimNotMacht{};

	// Allocamos memoria para una SimMatrix
	SimMatrix* sumPtr = new SimMatrix(m1.getDim());
	for(size_t i = 0; i < sumPtr->getDim(); i++){
		for(size_t j = 0; j <= i; j++)
			sumPtr->setElement(i, j, m1.getElement(i,j) + m2.getElement(i,j));
	}

	return sumPtr;
}

// Con amor, Cabre.