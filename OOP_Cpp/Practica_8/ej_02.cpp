/*
date: 19-09-2020
File: ej_02.cpp
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

class Figura{
public:
    virtual void dibujar() = 0;
};

class Cuadrado: public Figura{
public:
    void dibujar() override {
        std::cout << "Cuadrado::dibujar" << std::endl;
    }
};

class Triangulo : public Figura{
public:
    void dibujar() override {
        std::cout << "Triangulo::dibujar" << std::endl;
    }
};


int main(int argc, const char** argv){
    
    Figura* arr[] = {
        //new Figura,
        new Cuadrado,
        new Triangulo,
    };

    int i;

    for(i = 0; i < sizeof(arr)/sizeof(*arr); i++)
        arr[i]->dibujar();
    
    for(i = i-1; i >= 0; i--)
        delete arr[i];
    
    // Figura fail; // error: cannot declare variable ‘fail’ to be of abstract type ‘Figura’

    return 0;
}