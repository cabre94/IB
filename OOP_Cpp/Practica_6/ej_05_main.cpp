/*
date: 13-09-2020
File: ej_5.cpp
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

//#include "ej_5.h"
#include "ej_05.cpp"

int main(int argc, const char** argv){
    //local = 2;

    std::cout << "En main(), antes de llamar a func(), el valor de la variable es " << local << std::endl;

    func();

    std::cout << "En main(), despues de llamar a func(), el valor de la variable es: " << local << std::endl;

    return 0;
}