/*
date: 22-08-2020
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

void printDigit(int num){
    if(num < 10)
        std::cout << num;
    else
        std::cout << (char) ('A'+num-10);
}

void deBase10A(int num, int b){
    if (num >= b)
        deBase10A(num/b, b);
    printDigit(num % b);
}

int main(int argc, const char** argv) {
    int num, base;

    std::cout << "Ingrese numero en base decimal" << std::endl;
    std::cin >> num;

    std::cout << "Ingrese la base en la que lo quiere expresar (2-16)" << std::endl;
    std::cin >> base;

    std::cout << num << " en base " << base << " es ";
    deBase10A(num, base);
    std::cout << std::endl;
    return 0;
}