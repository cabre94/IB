/*
date: 12-09-2020
File: ej_2.cpp
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
    
public:
    A();	//Default constructor
    A(const A &);	//Copy constructor
    //A(A &&) = default;	//Move constructor
    //A &operator=(const A &) = default;	//Copy assignment
    //A &operator=(A &&) = default;	// Move assignment
    ~A();
};

A::A(){
    std::cout << "Constructor de " << this << std::endl;
}

A::~A(){
    std::cout << "Destructor de " << this << std::endl;
}

A::A(const A &){
    std::cout << "Copy constructor de " << this << std::endl;
}


void f(A a){
    std::cout << "Adentro de f, en donde se pasa un argumento por valor,";
    std::cout << " tenemos el argumento " << &a << std::endl;
}


A g(){
    std::cout << "En g, creo un objeto" << std::endl;
    A res;
    return res;
}

int main(int argc, const char** argv){
    std::cout << "Creo una variable dentro del main" << std::endl;

    A kk;
    
    std::cout << "Se lo paso a la funcion f" << std::endl;
    f(kk);
    std::cout << "Termino la llamada a la funcion f" << std::endl;

    std::cout << "Ahora llamo a la funcion g " << std::endl;

    g();
    //kk = g();

    std::cout << "Termino la llamada a la funcion g" << std::endl;

    return 0;
}