#include <iostream>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

using MensajeCifrado = vector<long>;

ostream &operator<<(ostream &os, const MensajeCifrado &msg) {
    os << '{';
    for( auto m : msg )
        os << m << ',';
    os << '}';
    return os;
}


long exponente_modular(long x, long e, long n)
{
    // TODO: punto a
}

void prueba_exponente_modular()
{
    long primos[] = {3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59};

    // Opcional: prueba de función exponente_modular
    //           (1 << (p-1)) % p == 1 
}

MensajeCifrado cifra(const string &s, long e, long n)
{
    // TODO: punto b
}

string descifra(const MensajeCifrado &msg, long d, long n)
{
    // TODO: punto c
}

void prueba_descifra()
{
    MensajeCifrado msg{4162,5524,789,1445,4537,3698,964,1273,4252,
                       1412,3698,6600,5526,5526,2759,2757,2333};
    long d = 1553;
    long n = 6767;

    // TODO: punto d
}

long rand_primo()
{
    // TODO: punto e
}

long coprimo(long r)
{
    // TODO: punto f
}

struct Terna {
    long x;
    long y;
    long mcd;
};

ostream &operator<<(ostream &os, const Terna &t) {
    return cout << "x: " << t.x << ", y: " << t.y << ", mcd: " << t.mcd; 
}

Terna eulerext(long a, long b)
{
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

Claves genera_claves()
{
    // TODO: punto h
}

void prueba()
{
    // TODO: punto i
}

int main()
{
    srand(time(nullptr));

    prueba_exponente_modular();

    prueba_descifra();

    prueba();

    return 0;
}
