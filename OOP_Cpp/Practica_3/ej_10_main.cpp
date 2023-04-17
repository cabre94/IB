/*
date: 28-08-2020
File: ej_10_main.cpp
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

#include "ej_10.h"

extern A a;

int main(int argc, const char** argv){

    std::cout << "Imprimo valor asignado al objeto en el otro .cpp" << std::endl;
    a.print();

    std::cout << "Modifico su valor y vuelvo a imprimirlo" << std::endl;
    a.setArg(8);
    a.print();

    /*
    g++ -c ej_10.cpp
    g++ -c ej_10_main.cpp
    g++ -o ej_10 ej_10.o ej_10_main.o
    ./ej_10
    */

    return 0;
}