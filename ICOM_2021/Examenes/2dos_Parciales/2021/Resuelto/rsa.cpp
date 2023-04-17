#include <iostream>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// De la practica 6 ejercicio 2
long MCD(long A, long B){
    if(B > A)
        MCD(B,A);
    if(B == 0)
        return A;
    else
        return MCD(B, A%B);
}



using MensajeCifrado = vector<long>;

ostream &operator<<(ostream &os, const MensajeCifrado &msg) {
    os << '{';
    for( auto m : msg )
        os << m << ',';
    os << '}';
    return os;
}


long exponente_modular(long x, long e, long n){
	if(e == 0)
		return 1;
	return ((x % n) * exponente_modular(x, e-1, n)) % n;
    // TODO: punto a
}

void prueba_exponente_modular(){
    long primos[] = {3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59};

	for(int i=0; i < (sizeof(primos) / sizeof(long)); i++)
		assert(exponente_modular(2, primos[i]-1, primos[i]) == 1);
    // Opcional: prueba de función exponente_modular
    //           (1 << (p-1)) % p == 1 
}

MensajeCifrado cifra(const string &s, long e, long n){
	MensajeCifrado msg; // vector<long>

	for(size_t i=0; i < s.size(); i++){
		msg.push_back(exponente_modular(s[i], e, n));
	}

	return msg;	
    // TODO: punto b
}

string descifra(const MensajeCifrado &msg, long d, long n){
	string s;

	for(size_t i=0; i < msg.size(); i++){
		s.push_back(exponente_modular(msg[i], d, n));
	}

	return s;
    // TODO: punto c
}

void prueba_descifra()
{
    MensajeCifrado msg{4162,5524,789,1445,4537,3698,964,1273,4252,
                       1412,3698,6600,5526,5526,2759,2757,2333};
    long d = 1553;
    long n = 6767;

	string s = descifra(msg, d, n);

	cout << "Mensaje descifrado" << s << endl;

    // TODO: punto d
}

long rand_primo(){
	long primo = rand() % 171 + 30;
	while(exponente_modular(2, primo-1, primo) != 1){
		primo = rand() % 171 + 30;
	}

	return primo;
    // TODO: punto e
}

long coprimo(long r){
	long e = 17;

	while (MCD(e, r) != 1){
		e += 2;
	}

	return e;
    // TODO: punto f
}

struct Terna{
    long x;
    long y;
    long mcd;
};

ostream &operator<<(ostream &os, const Terna &t) {
    return cout << "x: " << t.x << ", y: " << t.y << ", mcd: " << t.mcd; 
}

Terna eulerext(long a, long b){
	if(b == 0)
		return Terna{1, 0, a};
	
	Terna prima = eulerext(b, a%b);
	long x = prima.y;
	long y = prima.x - (a/b) * prima.y; // La division me hace ruido

	return Terna{x, y, prima.mcd};
    // TODO: punto g
}

struct Claves {
    long e;
    long d;
    long n;
};

ostream &operator<<(ostream &os, const Claves &c) {
    return cout << "{ e: " << c.e
                << ", d: " << c.d
                << ", n: " << c.n
                << " }";
}

Claves genera_claves(){
	long p = rand_primo();
	long q = rand_primo();

	while (p == q){
		q = rand_primo();
	}

	long r = (p-1) * (q-1);

	long e = coprimo(r);

	Terna t = eulerext(e,r);

	long d = t.x;

	if(d < 0)
		d = (d+r) % r;
	
	return Claves{e, d, p*q};


    // TODO: punto h
}

void prueba(){

	string msg = "La concha de la lora";

	Claves c = genera_claves();

	MensajeCifrado cifrado = cifra(msg, c.e, c.n);

	string descifrado = descifra(cifrado, c.d, c.n);

	cout << descifrado << endl;

}



int main()
{
    srand(time(nullptr));

    prueba_exponente_modular();

    prueba_descifra();

    prueba();

    return 0;
}
