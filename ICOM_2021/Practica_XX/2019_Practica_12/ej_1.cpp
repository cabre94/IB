#include "icom_helpers.h"

class Polinomio{
public:
	// construye un polinomio con los coeficientes y grado dados que
	// representa al polinomio:
	// coefs[0] + coefs[1]*x + coefs[2]*x^2 + ... + coefs[n]*x^n
	Polinomio(const double *c, int n);
	Polinomio(const Polinomio &p);
	~Polinomio();
	Polinomio &operator=(const Polinomio &p);
	Polinomio operator+(const Polinomio &p);
	Polinomio operator*(const Polinomio &p);
	double evaluate(double x); // evalua el polinomio en el valor x
	Polinomio derivate();
	// crea y retorna el polinomio derivado
	// crea y retorna el polinomio integrado con constante 'c'
	Polinomio integrate(double c);
	// Las siguientes son funciones auxiliares que no se piden en el ejercicio;
	// Polinomio();		// Todavia no se si hacer un constructor sin argumentos. En si no hace falta para que funcione todo, pero me da
						// paja que si o si haya que pasarle los coeficientes para declarar un objeto 'Polinomio'.
	int getGrado() const;
	void print();
private:
	// puntero a coeficientes
	double *coefs;
	int grado;
};

int main(){
	double a[5] = {2,5,0,-3,3};
	int grado_a = sizeof(a)/sizeof(double) - 1;

	double b[6] = {4,2,1,43,5,3};
	int grado_b = sizeof(b)/sizeof(double) - 1;

	Polinomio p1(a,grado_a), p2(b,grado_b);

	cout << "p1 = " << endl; p1.print();
	cout << endl;
	cout << "p2 = " << endl; p2.print();
	cout << endl;

	Polinomio p3 = p1 + p2;
	cout << "p3 = p1 + p1" << endl; p3.print();
	cout << endl;

	p3 = p3.derivate();
	cout << "Derivo p3 una vez:" << endl;
	p3.print();
	cout << "Derivo p3 otra vez:" << endl;
	p3 = p3.derivate();
	p3.print();
	cout << endl;
	
	cout << "Integro una, dos y tres veces, todas con c = 0" << endl;
	p3 = p3.integrate(0);
	p3.print();
	p3 = p3.integrate(0);
	p3.print();
	p3 = p3.integrate(0);
	p3.print();
	cout << endl;
	
	cout << "p4 = p1 * p2" << endl;
	Polinomio p4 = (p1*p2);
	p4.print();
	cout << endl;

	cout << "Por ultimo, evaluo p4(x = 0) = " << p4.evaluate(0) << endl;

	return 0;
}

Polinomio::Polinomio(const double *c, int n){
	grado = n;
	coefs = new double[grado+1];
	for(int i=0; i <= grado; i++)
		coefs[i] = c[i];
}

Polinomio::Polinomio(const Polinomio &p){
	grado = p.getGrado();
	coefs = new double[grado+1];
	for(int i=0; i <= grado; i++)
		coefs[i] = p.coefs[i];
}

Polinomio::~Polinomio(){
	delete [] coefs;
}

int Polinomio::getGrado() const{
	return grado;
}

Polinomio &Polinomio::operator=(const Polinomio &p){
	double *aux = new double[p.getGrado()+1];
	for(int i=0; i <= p.getGrado(); i++)
		aux[i] = p.coefs[i];
	grado = p.getGrado();
	delete [] coefs;
	coefs = aux;
	return *this;
}

Polinomio Polinomio::operator+(const Polinomio &p){
	Polinomio a(p);
	if(grado < p.getGrado()){
		for(int i=0; i <= grado; i++)
			a.coefs[i] = p.coefs[i] + coefs[i];
	}else{
		a = *this;
		for(int i=0; i <= p.getGrado(); i++)
			a.coefs[i] = p.coefs[i] + coefs[i];
	}
	return a;
}

Polinomio Polinomio::operator*(const Polinomio &p){
	double *coefs_prod = new double[grado+p.getGrado()+1];
	for(int i=0; i <= (grado + p.getGrado()); i++)
		coefs_prod[i] = 0;
	for(int i=0; i <= grado; i++)
		for(int j=0; j <= p.getGrado(); j++)
			coefs_prod[i+j] += (p.coefs[j] * coefs[i]);
	Polinomio res(coefs_prod, grado + p.getGrado());
	delete [] coefs_prod;
	return res;
}

double Polinomio::evaluate(double x){
	int suma = 0;
	for(int i=0; i <= grado; i++)
		suma += coefs[i] * pow(x,i);
	return suma;
}

Polinomio Polinomio::derivate(){
	double *coefs_der = new double[grado];
	for(int i=0; i < grado; i++)
		coefs_der[i] = (i+1)*coefs[i+1];
	Polinomio res(coefs_der,grado-1);
	return res;
}

Polinomio Polinomio::integrate(double c){
	double *coefs_int = new double[grado+2];
	coefs_int[0] = c;
	for(int i=1; i <= grado+1; i++)
		coefs_int[i] = ((coefs[i-1]) / i);
	Polinomio res(coefs_int,grado+1);
	delete [] coefs_int;
	return res;
}

void Polinomio::print(){
	cout << coefs[0];
	for(int i=1; i <= grado; i++){
		if(coefs[i] > 0)
			cout << " + " << coefs[i] << "*x^" << i;
		else if(coefs[i] < 0)
			cout << " - " << abs(coefs[i]) << "*x^" << i;
	}
	cout << endl;
}

// Con amor, Cabre.