/*
 * Copyright del enunciado: Pablo Cornaglia
 *
 */

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
    if( e == 0 )
        return 1;
    return (x % n) * (exponente_modular(x, e - 1, n)) % n;
}

void prueba_exponente_modular()
{
    long primos[] = {3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59};

    for( auto p : primos )
        assert(exponente_modular(2, p-1, p) == 1);
}

MensajeCifrado cifra(const string &s, long e, long n)
{
    MensajeCifrado cifrado;
    cifrado.reserve(s.size());

    for( auto c : s )
        cifrado.push_back(exponente_modular(c, e, n));
        
    return cifrado;
}

string descifra(const MensajeCifrado &msg, long d, long n)
{
    string s;

    for( auto x : msg )
        s.push_back(exponente_modular(x, d, n));
        
    return s;
}

void prueba_descifra()
{
    MensajeCifrado msg{4162,5524,789,1445,4537,3698,964,1273,4252,
                       1412,3698,6600,5526,5526,2759,2757,2333};
    long d = 1553;
    long n = 6767;

    cout << "prueba_descifra: " << descifra(msg, d, n) << endl;
}

long rand_primo()
{
    long primo;
    
    do {
        primo = 30 + rand() % 171;
    } while( exponente_modular(2, primo - 1, primo) != 1 );

    return primo;
}

long mcd(long a, long b)
{
    if( b == 0 )
        return a;
    return mcd(b, a % b);
}

long coprimo(long r)
{
    long e = 17;

    while( mcd(e, r) != 1 )
        e += 2;

    return e;
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
    if( b == 0 )
        return { 1, 0, a };

    auto t = eulerext(b, a % b);

    return { t.y, t.x - (a/b) * t.y, t.mcd };
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
    long p = rand_primo();
    long q = rand_primo();
    while( p == q )
        q = rand_primo();

    long r = (p - 1) * (q - 1);

    long e = coprimo(r);

    auto t = eulerext(e, r);

    long d = t.x;
    if( d < 0 )
        d = (d + r) % r;

    return { d, e, /* p, q, */ p * q };
}

void prueba(int n)
{
    string frase = "2do Parcial ICOM 2020";

    for( int i = 0; i < n; ++i ) {
        auto claves = genera_claves();
        cout << "test " << i+1 << ": claves: " << claves << endl;
        auto cifrado = cifra(frase, claves.e, claves.n);
        cout << "  cifrado: " << cifrado << endl;
        auto descifrado = descifra(cifrado, claves.d, claves.n);
        cout << "  descifrado: " << descifrado << endl;
        if( descifrado != frase )
            cout << " ### Error!!! #####\n";
    }
}

int main()
{
    srand(time(nullptr));

    prueba_exponente_modular();

    prueba_descifra();

    prueba(200);

    return 0;
}