/*
date: 23-08-2020
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

#include "misfuncs.h"


// retorna la cantidad de bits en '1' presentes en la representacion de value
int numOnes(int value){
    int count = 0;
    while (value != 0){
        count += (value & 1);
        value >>= 1;        
    }
    return count;
}

// devuelve el valor 'value', con el bit 'bit' en 1
int setBit(int value, int bit){
    int aux = 1<<bit;   // El bit 0 es el menos significativo
    return value | aux;
}

// devuelve el valor 'value', con el bit 'bit' en 0
int resetBit(int value, int bit){
    if( (value >> bit)%2 )      // Esto me dice si tiene un '0' o un '1'
        value -= (1<<bit);
    return value;
}

// chequea si el bit 'bit' esta en 1
bool testBit(int value, int bit){
    return (bool) ((value >> bit)%2);
}


int main(int argc, const char** argv) {

    int i = 235;
    deBase10A(i,2);
    std::cout << std::endl;
    std::cout << "Cantidad de \'1\' " << numOnes(i) << std::endl;

    int aux = setBit(i,4);
    deBase10A(aux,2);
    std::cout << std::endl;
    std::cout << "Cantidad de \'1\' " << numOnes(aux) << std::endl;

    aux = resetBit(i,5);
    deBase10A(aux,2);
    std::cout << std::endl;
    std::cout << "Cantidad de \'1\' " << numOnes(aux) << std::endl;

    if(testBit(i,5))
        std::cout << "El bit 5 esta en 1" << std::endl;
    else
        std::cout << "El bit 5 esta en 0" << std::endl;

    i = resetBit(i,5);
    if(testBit(i,5))
        std::cout << "El bit 5 esta en 1" << std::endl;
    else
        std::cout << "El bit 5 esta en 0" << std::endl;

    return 0;
}
