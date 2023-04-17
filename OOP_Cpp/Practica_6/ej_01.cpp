/*
date: 12-09-2020
File: ej_1.cpp
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
public:
    double x;
    A(double x_ = 0) : x{x_} {}
    void print(){std::cout << "El contenido es " << x << std::endl;}

};


int main(int argc, const char** argv){

    double A::*pmDouble;                 // Puntero a miembro tipo double de la clase A
    pmDouble = &A::x;                    // Se lo asigno al miembro x de A
    //double A::*pmDouble = &A::x        // Todo en una linea

    void (A::*pmf) ();                  // Puntero a funcion miembro de A que no toma nada ni retorna nada
    pmf = &A::print;                    // Se lo asigno a metodo print de A 
    
    A a(42), *pa = &a;

    std::cout << "printeo con (a.*pmf)(): ";
    (a.*pmf)();
    std::cout << "printeo con (pa->*pmf)(): ";
    (pa->*pmf)();

    std::cout << std::endl << "Modifico el valor del dato miembro con a.*pmDouble" << std::endl;
    a.*pmDouble = 14;

    std::cout << "printeo con (a.*pmf)(): ";
    (a.*pmf)();
    std::cout << "printeo con (pa->*pmf)(): ";
    (pa->*pmf)();

    std::cout << std::endl << "Modifico el valor del dato miembro con pa->*pmDouble" << std::endl;
    pa->*pmDouble = 69;

    std::cout << "printeo con (a.*pmf)(): ";
    (a.*pmf)();
    std::cout << "printeo con (pa->*pmf)(): ";
    (pa->*pmf)();

    return 0;
} 