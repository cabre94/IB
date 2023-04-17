/*
date: 27-08-2020
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

class Prueba{
public:
    int fun();
    void print();
};

int Prueba::fun(){
    return 0;
}

void Prueba::print(){
    std::cout << "KK" << std::endl;
}

int main(int argc, const char** argv) {

    Prueba a, b, c, d;

    Prueba arr[] = {a, b, c, d};

    int size = sizeof(arr)/sizeof(Prueba);

    for(int i=0; i < size; i++)
        arr[i].print();

    return 0;
}