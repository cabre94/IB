/*
date: 24-10-21
File: 01_limite_de_una_serie.cpp
Author : Facundo Martin Cabrera
Email: cabre94@hotmail.com facundo.cabrera@ib.edu.ar
GitHub: https://github.com/cabre94
GitLab: https://gitlab.com/cabre94
Description: 
*/


#include <iostream>
#include <cmath>

using namespace std;


class Serie{
public:
	// retorna el valor del termino i-esimo de la serie
	virtual double operator()(int i) = 0;
};

struct NotConvergeException{};

// Clase geometricSeries heredada de Serie para series geometricas
class geometricSeries : public Serie{
	double a, r;
public:
	geometricSeries(double a_, double r_) : a(a_), r(r_) {}
	double operator()(int i){return a*pow(r,i);}
};

// Clase alternatingSeries heredada se Serie para series alternadas chotas
// del tipo   a^n * (1 / (c1*n+c2)). Cualquier cosa mas complicada que esto
// requiere hacer mejor las clases. a deberia ser negativo
class alternatingSeries : public Serie{
	double a, c1, c2;
public:
	alternatingSeries(double a_, double c1_, double c2_)
		: a(a_), c1(c1_), c2(c2_) {}
	double operator()(int i){return pow(a,i) * (1.0/(c1*i+c2));}
};


double limiteSerie(int M, Serie &serie, double cota_error);


int main(){

	// Primer caso
	Serie *s = new geometricSeries(1, 0.5);
	try{
		cout << limiteSerie(10000, *s, 1e-7) << endl;
		cout << "Deberia converger a " << 2 << endl;
	}catch(NotConvergeException){
		cout << "La serie no converge" << endl;
	}
	delete s;

	// Segundo
	s = new geometricSeries(1, 1.0/M_PI);
	try{
		cout << limiteSerie(10000, *s, 1e-7) << endl;
		cout << "Deberia converger a " << (M_PI)/(M_PI-1) << endl;
	}catch(NotConvergeException){
		cout << "La serie no converge" << endl;
	}
	delete s;

	// Tercero
	s = new alternatingSeries(-3.0, 2.0, 1.0);
	try{
		cout << limiteSerie(10000, *s, 1e-7) << endl;
		cout << "Esto no deberia printearse" << endl;
	}catch(NotConvergeException e){
		cout << "La serie no converge" << endl;
	}
	delete s;



	return 0;
}


double limiteSerie(int M, Serie &serie, double cota_error){

	int i = 0;
	double limit = 0, s_i;
	bool converge = false;

	// Mientras no superemos la cantidad maxima de iteraciones
	// o la serie no converja, seguimos iterando
	while(i < M && !converge){
		s_i = serie(i);	// Calculamos el i-esimo termino y sumamos
		limit += s_i;

		// Si el termino es menor que una cota, tomamos como que converge
		if(abs(s_i) < cota_error)
			converge = true;
		i++;
	}

	// Si no convergio, lanzamos la excepcion
	if(!converge)
		throw NotConvergeException{};
	return limit;
}