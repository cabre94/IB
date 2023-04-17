/*
date: 16-09-2020
File: ej_7.cpp
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
    double x;
public:
    A(double x_=0) : x{x_} {std::cout << "Constructor" << std::endl;}
    ~A(){std::cout << "Destructor" << std::endl;}

    void* operator new(size_t);
    void operator delete(void*);
};

void* A::operator new(size_t sz){
    std::cout << "Creando memoria" << std::endl;
    void *m = malloc(sz);
    if(!m)
        std::cout << "KK negra" << std::endl;
    return m;
}

void A::operator delete(void *m){
    std::cout << "Destruyendo memoria" << std::endl;
    free(m);
}


int main(int argc, const char** argv){
    A *a = new A;

    delete a;
    
    return 0;
}