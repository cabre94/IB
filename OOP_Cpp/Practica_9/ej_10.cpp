/*
date: 27-09-2020
File: ej_10.cpp
Author : Facundo Martin Cabrera
Email: cabre94@hotmail.com facundo.cabrera@ib.edu.ar
GitHub: https://github.com/cabre94
GitLab: https://gitlab.com/cabre94
Description:
*/

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <sstream>

#define N (8*sizeof(uint64_t))


template<class T>
class Vector{
private:
    T *v;
    int sz;

public:
    Vector() : v(nullptr), sz(0) {}	            //Default constructor
    Vector(int sz_) : v(new T[sz_]), sz(sz_) {}
    ~Vector(){ delete [] v;};

    Vector(const Vector &);	            //Copy constructor
    Vector(Vector &&);	                //Move constructor

    Vector &operator=(const Vector &);	//Copy assignment
    Vector &operator=(Vector &&);	    // Move assignment

    T& operator[](int i) const {return v[i];}

    int getSize(){return sz;}
    
    template <class U> friend std::ostream& operator<<(std::ostream &out, Vector<U> &vec);

private:
    void swap(Vector<T> &other);
};


template<class T>
Vector<T>::Vector(const Vector<T> &vec) : v(new T[vec.sz]), sz(vec.sz){
    for(int i=0; i < sz; i++)
        v[i] = vec.v[i];
}

template<class T>
Vector<T>::Vector(Vector &&vec) : v(nullptr), sz(vec.sz){
    this->swap(vec);
}

template<class T>
Vector<T> &Vector<T>::operator=(const Vector &vec){
    T *aux = new T[vec.sz];
    for(int i=0; i < vec.sz; i++)
        aux[i] = vec.v[i];
    delete [] v;
    v = aux;
    sz = vec.sz;
    return *this;
}

template<class T>
Vector<T> &Vector<T>::operator=(Vector &&vec){
    this->swap(vec);
    sz = vec.sz;
    return *this;
}

template<class T>
void Vector<T>::swap(Vector<T> &other){
    using std::swap;
    swap(v, other.v);
}

template <class T>
std::ostream& operator<<(std::ostream &out, Vector<T> &vec){
    for(int i=0; i < vec.sz-1; i++)
        out << vec[i] << " - ";
    out << vec[vec.sz-1];
    return out;
}


/*
Especializacion para bools
*/


template<>
class Vector<bool>{
private:
    uint64_t *v;
    int bits;       // Cantidad de bits
    int sz;         // Cantidad de elementos de v
public:
    Vector() : v(nullptr), bits(0), sz(0) {}
    Vector(int bits_) : v(new uint64_t[1+bits_/N]), bits(bits_), sz(1+bits_/N) {}
    ~Vector(){ delete [] v;};

    Vector(const Vector &);	            //Copy constructor
    Vector(Vector &&);	                //Move constructor

    Vector &operator=(const Vector &);	//Copy assignment
    Vector &operator=(Vector &&);	    //Move assignment

    // bool& operator[](int i); // Otro dia...

    void set(int bit, bool value);
    int getSize(){return bits;}     // No retorna realmente size, pero es lo que el usuario esperaria

    friend std::ostream& operator<<(std::ostream &out, Vector<bool> &vec);

private:
    
    void swap(Vector &other);
};


Vector<bool>::Vector(const Vector<bool> &vec) : v(new uint64_t[vec.sz]), bits(vec.bits), sz(vec.sz){
    for(int i=0; i < vec.sz; i++)
        v[i] = vec.v[i];
}

Vector<bool>::Vector(Vector &&vec) : v(nullptr), bits(vec.bits), sz(vec.sz){
    this->swap(vec);
}

Vector<bool> &Vector<bool>::operator=(const Vector<bool> &vec){
    uint64_t* aux = new uint64_t[vec.sz];

    for(int i=0; i < vec.sz; i++)
        aux[i] = vec.v[i];

    delete [] v;
    v = aux;
    bits = vec.bits;
    sz = vec.sz;
    return *this;
}

Vector<bool> &Vector<bool>::operator=(Vector<bool> &&vec){
    this->swap(vec);
    bits = vec.bits;
    sz = vec.sz;
    return *this;
}

void Vector<bool>::swap(Vector &other){
    using std::swap;
    swap(v, other.v);
}

void Vector<bool>::set(int i, bool value){
    if(value)
        v[i/N] |= 1ULL << (i % (N));
    else
        v[i/N] &= ~(1ULL << (i % N));
}

std::ostream& operator<<(std::ostream &out, Vector<bool> &vec){
    for(int i=0; i < vec.bits; i++)
        out << ( vec.v[i/(N)] >> (i%(N)) ) % 2;
    return out;
}




int main(int argc, const char** argv){

    srand(time(NULL));

    Vector<int> vec(10);

    for(int i=0; i < vec.getSize(); i++)
        vec[i] = rand() % 10;
    
    std::cout << "Vector original: " << vec << std::endl;

    Vector<int> vec2 = vec;                     // Copy constructor
    std::cout << "Con copy constructor: " << vec2 << std::endl;

    Vector<int> vec3 = std::move(vec);          // Move Constructor
    std::cout << "Con move constructor: " << vec3 << std::endl;

    Vector<int> vec4;
    vec4 = vec2;                                // Copy assigment
    std::cout << "Con copy assigment  : " << vec4 << std::endl;

    vec4 = std::move(vec3);                     // Move assigment
    std::cout << "Con move assigment  : " << vec4 << std::endl;

    

    //////////////////////////////////////////////////////////
    // srand(time(NULL));

    Vector<bool> vec_b(65);

    for(int i=0; i<vec_b.getSize(); i++)
        vec_b.set(i, rand() % 2);

    std::cout << "\nVector<bool> original:" << vec_b << std::endl;

    Vector<bool> vec_b2 = vec_b;                // Copy constructor    
    std::cout << "Con copy constructor: " << vec_b2 << std::endl;

    Vector<bool> vec_b3 = std::move(vec_b);     // Move constructor
    std::cout << "Con move constructor: " << vec_b3 << std::endl;
    
    Vector<bool> vec_b4;
    vec_b4 = vec_b2;                            // Copy assigment
    std::cout << "Con copy assigment  : " << vec_b4 << std::endl;

    Vector<bool> vec_b5;
    vec_b5 = std::move(vec_b3);                 // Move assigment
    std::cout << "Con move assigment  : " << vec_b5 << std::endl;


    return 0;
}