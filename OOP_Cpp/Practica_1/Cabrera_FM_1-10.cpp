#include <iostream>
#include <vector>

using namespace std;

struct Complex{
	double re, im;

	Complex(double r, double i) { re = r; im = i; }
	Complex(double r) { re = r; im = 0; }
	Complex() { re = im = 0; }

	Complex operator+(Complex);
	Complex operator-(Complex);
	Complex operator*(Complex);
	Complex operator/(Complex);

    // Saque la idea de aca https://www.geeksforgeeks.org/overloading-stream-insertion-operators-c/
    // pero no entiendo del todo porque hay que ponerles friend, capaz son funciones de alguna otra clase.
    friend ostream& operator << (ostream &out, Complex &c);
    friend istream& operator >> (istream &in,  Complex &c);
	
};



Complex Complex::operator+(Complex a){
	Complex res = {re + a.re, im + a.im};
	return res;
}

Complex Complex::operator-(Complex a){
	Complex res = {re - a.re, im - a.im};
	return res;
}

Complex Complex::operator*(Complex a){
	Complex res = {re*a.re - im*a.im, re*a.im + im*a.re};
	return res;
}

Complex Complex::operator/(Complex a){
	Complex res = { (re*a.re + im*a.im) / (a.re*a.re + a.im*a.im),
					(im*a.re - re*a.im) / (a.re*a.re + a.im*a.im)};
	return res;
}

ostream& operator <<(ostream &out, Complex &c){

	if(c.re == 0 && c.im ==0)
		out << 0;
	else if(c.re != 0)
		out << c.re;

	if(c.im == 1 && c.re == 0)
		out << "i";
	else if(c.im == 1)
		out << "+i";
	else if(c.im == -1)
		out << "-i";
	else if(c.im > 0)
		out << "+i" << c.im;
	else if(c.im < 0)
		out << "-i" << -1*c.im;

    return out;
}

istream& operator >>(istream &in,  Complex &c){

	cout << "Ingresar la parte real: ";
	in >> c.re;
	cout << "Ingresar la parte imaginaria: ";
	in >> c.im;

	return in;
}

int main(){

	Complex c1, c2, c3;

	cin >> c1;
	cin >> c2;

	cout << "El primer complejo es c1 = " << c1 << endl;
	cout << "El segundo complejo es c2 = " << c2 << endl;


	// No se porque no puedo imprimir directamente c1+c2, lo tuve que guardar en otra variable para imprimir
	c3 = c1 + c2;
	cout << "c1 + c2 = " << c3 << endl;

	c3 = c1 - c2;
	cout << "c1 - c2 = " << c3 << endl;
	
	c3 = c1 * c2;
	cout << "c1 * c2 = " << c3 << endl;

	c3 = c1 / c2;	
	cout << "c1 / c2 = " << c3 << endl;

	return 0;
}