/*
date: 16-09-2020
File: ej_08.cpp
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

#include "stack.h"



class A{
private:
    static Stack<int> available;
    static uint8_t buffer[]; 

    // Poner el constructor en privado
    ~A();

public:
    static const int MAX = 5;

    A();

    A(const A &) = delete;	//Copy constructor
    A(A &&) = delete;	    //Move constructor
    A &operator=(const A &) = delete;	//Copy assignment
    A &operator=(A &&) = delete;	    // Move assignment

    void* operator new(size_t);
    void  operator delete(void*);
    
    void* operator new[](size_t) = delete;
    void  operator delete[](void*) = delete;
    
    void* operator new(size_t, const std::nothrow_t&) = delete;
    void* operator new[](size_t, const std::nothrow_t&) = delete;
    void  operator delete(void*, const std::nothrow_t&) = delete;
    void  operator delete[](void*, const std::nothrow_t&) = delete;
    
    void* operator new(size_t, void* ) = delete;
    void* operator new[](size_t, void*) = delete;
    void  operator delete(void*, void*) = delete;
    void  operator delete[](void*, void*) = delete;

    static void destroy(A *a);

    static void initializer();
};

namespace {
    A *heap = nullptr;
}

// Instancio el buffer
uint8_t A::buffer[A::MAX * sizeof(A)];
// Instancio el Stack que tiene los indices 
Stack<int> A::available = Stack<int>(A::MAX);


A::A(){
    std::cout << "A::A() @ " << this << std::endl;
}

A::~A(){
    std::cout << "A::~A() @ " << this << std::endl;
}

void A::destroy(A *a){
    delete a;
}

void A::initializer(){
    heap = (A *) A::buffer;
    for(int i=0; i < MAX; i++)
        A::available.push(i);
}


void* A::operator new(size_t sz){
    if(available.isEmpty())
        throw std::bad_alloc{};
    
    int index = available.pop();
    return (A *) buffer + index+sizeof(A);
}

void  A::operator delete(void* a){
    A *pa = (A *) a;
    int index = (int) (pa - heap);
    available.push(index);
}



int main(int argc, const char** argv){
    A::initializer();

    const int MAX_REQ = 70;
    A *ptrs[MAX_REQ];

    int k;

    try {
        // Loop de alocación por prueba
        for( k = 0; k < MAX_REQ; ++k )
            ptrs[k] = new A;
    } catch( const std::exception &e ) {
        // Atrapamos cualquier excepción de la STL
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // A cuánto llegamos en el loop de alocación
    std::cout << "Allocamos: " << k << std::endl;

    // Mezclamos el arreglo de punteros allocados para liberarlos
    // en un orden aleatorio
    std::random_shuffle(ptrs, &ptrs[k]);

    while( k-- )
        A::destroy(ptrs[k]);

    return 0;
}