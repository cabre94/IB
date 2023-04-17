/*
date: 25-08-2020
File: ej_2.cpp
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

unsigned long long int fibonacci(bool reset = false){
    static unsigned long long int f1 = 0, f2 = 1;
    if(reset){
        f1 = 0;
        f2 = 1;        
    }else{
        unsigned long long int aux = f2 + f1;
        f1 = f2;
        f2 = aux;
    }
    return f1;
}

int main(int argc, const char** argv) {

    for(int i=1; i<=50; i++)
        std::cout << "Termino " << i << "-esimo: " << fibonacci() << std::endl;
    
    std::cout << "Reseteo y vuelvo a imprimir 20 terminos" << std::endl;
    fibonacci(true);
    for(int i=0; i<=20; i++)
        std::cout << "Termino " << i << "-esimo: " << fibonacci() << std::endl;

    return 0;
}