/*
date: 12-09-2020
File: ej_4.cpp
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
#include <cstdlib>

class A{
private:
    double *ptr;
    
public:
    A(double);	//Default constructor
    A(const A &a, int k=10);	//Copy constructor
    A(A &&) = default;	//Move constructor
    A &operator=(const A &) = default;	//Copy assignment
    A &operator=(A &&) = default;	// Move assignment
    ~A();
};

A::A(double x){
    ptr = new double;
    *ptr = x;
}

A::A(const A &a, int k): ptr{ new double }{
    std::cout << "Copy constructor" << std::endl;
    *ptr = *a.ptr;
}


A::~A(){
    std::cout << "En ~A() el contenido es: " << *ptr << std::endl;
    *ptr = -1;
    delete ptr;
    ptr = 0; // No se si hace falta esto
}



void f(A a){
    std::cout << "Cuerpo de f()..." << std::endl;
}



int main(int argc, const char** argv){
    
    A kk(42);

    f(kk);

    /*
    La salida antes de corregirlo es:

    Cuerpo de f()...
    En ~A() el contenido es: 42
    En ~A() el contenido es: 0
    free(): double free detected in tcache 2
    Aborted (core dumped)
    */

    /*
    La solución es implementar un constructor copia propio que haga todo
    lo necesario para tener dos objetos independientes.

    Despues de implementarlo, la salida es

    Cuerpo de f()...
    En ~A() el contenido es: 42
    En ~A() el contenido es: 42
    */



    return 0;
}