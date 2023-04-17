/*
date: 16-09-2020
File: ej_09.cpp
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

class Rueda{
public:
    Rueda(){std::cout << "Rueda" << std::endl;}
};

class Motor{
public:
    Motor(){std::cout << "Motor" << std::endl;}
};

class Ventanilla{
public:
    Ventanilla(){std::cout << "Ventanilla" << std::endl;}
};

class Puerta{
private:
    Ventanilla v;
public:
    Puerta(){std::cout << "Puerta" << std::endl;}
};

class Vehiculo{
private:
    Motor m; // Bicicletas no cuentan. Moto no tiene puerta y barco no tiene ruedas.
public:
    Vehiculo(){std::cout << "Vehiculo" << std::endl;}
};

class Auto : public Vehiculo{
private:
    Rueda r;
    Puerta p;
public:
    Auto(){std::cout << "Auto" << std::endl;}
};



int main(int argc, const char** argv){
    
    Auto car;

    return 0;
}