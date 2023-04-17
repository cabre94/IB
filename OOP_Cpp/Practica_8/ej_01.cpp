/*
date: 19-09-2020
File: ej_01.cpp
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
    virtual void dibujar(){
    // void dibujar(){          // Para ver la diferencia, se puede cambiar por esta linea y sacarle el override al resto
        std::cout << "Figura::dibujar" << std::endl;
    }
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
        new Figura,
        new Cuadrado,
        new Triangulo,
    };

    int i;

    for(i = 0; i < sizeof(arr)/sizeof(*arr); i++)
        arr[i]->dibujar();
    
    for(i = i-1; i >= 0; i--)
        delete arr[i];

    return 0;
}