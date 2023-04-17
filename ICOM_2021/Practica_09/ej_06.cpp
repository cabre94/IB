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
	SimMatrix &operator=(const SimMatrix &);	
	~SimMatrix();

	void setElement(int i, int j, double val);
	double getElement(int i, int j) const;
	size_t getDim() const{return dim;};

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

	// ej 6
	SimMatrix m3(n);
	m3 = m1;		// Hacer esto no es lo mismo que hacer SimMatrix m3 = m1;
					// Aca se usa el operator= porque YA EXISTE una matriz m3
					// que tiene "cosas". Entonces no solo hay que copiar m1 2n m3
					// si no que ademas hay que liberar lo que hay en m3 antes de copiar
	cout << "\nm1 = " << endl;
	m1.print();
	cout << "\nm3 = " << endl;
	m3.print();

	/* Si no definimos el SimMatrix &operator=(const SimMatrix &);
	explota a la mierda todo */



	cout << "\nAhora imprimo la copia\n\n";
	SimMatrix m4 = m1;
	m4.print();

	cout << "\nSuma" << endl;
	SimMatrix *suma = sumaSimMatrix(m1, m4);
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

/* Se puede hacer como esta comentado abajo, pero esta forma es mejor, porque
si por X motivo falla la alocacion (tira bad_alloc) y ya destruiste el
contenido, cagaste. Con esto solo lo destruis una vez que te aseguraste de
haberlo copiado.*/
SimMatrix& SimMatrix::operator=(const SimMatrix &m){
	// Allocamos memoria en un puntero axiliar
	vector<double>* aux = new vector<double>[m.getDim()];

	for(size_t i = 0; i < m.getDim(); i++){	// Copiamos
		aux[i] = m.values[i];
	}

	// Ahora si, como estamos seguros de que pudimos copiar la Matriz, liberamos
	// la memoria de la matriz actual y reemplazamos el puntero por el auxiliar,
	// donde ya esta todo copiado.
	dim = m.getDim();
	delete [] values;
	values = aux;	// Guardamos la direccion de memoria donde esta todo copiado
					// en values
	
	// Retornamos una referencia, asi que pedimos el contenido de this
	return *this;
}

/*SimMatrix& SimMatrix::operator=(const SimMatrix &m){
	// Primero eliminamos la memoria
	
	
	/*delete [] values;
	// 
	dim = m.getDim();
	values = new vector<double> [dim];

	for(size_t i = 0; i < dim; i++)
		values[i].resize(i+1);
	
	for(size_t i = 0; i < dim; i++){
		for(size_t j = 0; j <= i; j++)
			setElement(i, j, m.getElement(i, j));
	}

	return *this;
}*/

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

SimMatrix *sumaSimMatrix(const SimMatrix &m1, const SimMatrix &m2){
	if(m1.getDim() != m2.getDim())
		throw dimNotMacht{};

	SimMatrix* sumPtr = new SimMatrix(m1.getDim());
	for(size_t i = 0; i < sumPtr->getDim(); i++){
		for(size_t j = 0; j <= i; j++)
			sumPtr->setElement(i, j, m1.getElement(i,j) + m2.getElement(i,j));
	}

	return sumPtr;
}

/*
Algunas aclaraciones:

Porque lo que retorna el operator= es una referencia a una matriz y no puede
ser void por ejemplo?
Bueno, C++ permite hacer cosas de este estilo: a = b = c; y si uno lo define void,
no lo puede hacer. Para entenderlo:
Cuando haces a = b; esto es como hacer a.operator=(b); Nadie usa el operator=
asi, tendrias que ser un degenerado, pero para esto asi es mas claro.
Entonces cuando haces a = b = c; lo podes pensar como
a.operator=(b.operator=(c));
Ahi queda mas claro que para que el argumento que recibe a.operator=(...); sea
una matrix, entonces b.operator=(c) tiene que retornar una matriz.
*/

// Con amor, Cabre.