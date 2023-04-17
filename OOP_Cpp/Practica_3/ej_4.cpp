/*
date: 26-08-2020
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

#include "misfuncs.h"


int main(int argc, const char** argv) {

    Stack<std::string> estac(100);
    std::string arr[5] = {"Aguante","Boca","Gallina","put*","B"};

    std::cout << "Meto algunos valores al azar e imprimo el Stack:" << std::endl;
    for(int i=0; i<5; i++)
        estac.push(arr[i]);
    std::cout << estac << std::endl;


    std::cout << "Saco un par de valores:" << std::endl;
    for(int i=0; i<3; i++)
        std::cout << "Saco: " << estac.pop() << std::endl;
    
    std::cout << "Imprimo lo que quedo en el Stack:" << std::endl;
    std::cout << estac << std::endl;

    return 0;
}


