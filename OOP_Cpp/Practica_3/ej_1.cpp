/*
date: 25-08-2020
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

void modChar(char &c){
    c = 'o';
}

int main(int argc, const char** argv) {
    char c = 'k';
    std::cout << "Primero el char es: " << c << std::endl;

    modChar(c);
    std::cout << "Despues de llamar a la funcion que lo modifica es: " << c << std::endl;
    return 0;
}