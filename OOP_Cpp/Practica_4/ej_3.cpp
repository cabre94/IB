/*
date: 27-08-2020
File: ej_3.cpp
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
    int a;
};

class B{
    int func(){return 0;}
};

class C{
    int a;
    int func(){return 0;}
};

class D{
    double a;
};

class E{
    double func(){return 0;}
};

class F{
    double a;
    double func(){return 0;}
};

int main(int argc, const char** argv) {

    std::cout << "Tamaño de objeto A: " << sizeof(A) << std::endl;
    std::cout << "Tamaño de objeto B: " << sizeof(B) << std::endl;
    std::cout << "Tamaño de objeto C: " << sizeof(C) << std::endl;
    std::cout << "Tamaño de objeto D: " << sizeof(D) << std::endl;
    std::cout << "Tamaño de objeto E: " << sizeof(E) << std::endl;
    std::cout << "Tamaño de objeto F: " << sizeof(F) << std::endl;

    return 0;
}