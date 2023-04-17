/*
date: 26-09-2020
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
#include <typeinfo>

// static unsigned long long int f1 = 0, f2 = 1;

template<class T>
T fibonacci(bool reset=false){
    // static unsigned long long int f1 = 0, f2 = 1;
    static T f1 = 0, f2 = 1;
    if(reset){
        f1 = 0;
        f2 = 1;
    }else{
        T aux = f1 + f2;
        f1 = f2;
        f2 = aux;
    }
    return f1;
}


int main(int argc, const char** argv) {

    int i, j;
    for(i=1; i <= 10; i++)
        std::cout << "Termino " << i << "-esimo: " << fibonacci<int>() << " " << typeid(fibonacci<int>()).name() << std::endl;
    // fibonacci<int>(true);
    for(j=1; j <= 10; j++)
        std::cout << "Termino " << j << "-esimo: " << fibonacci<double>() << " " << typeid(fibonacci<double>()).name() << std::endl;
    fibonacci<double>(true);
    for(; i <= 20; i++)
        std::cout << "Termino " << i << "-esimo: " << fibonacci<int>() << " " << typeid(fibonacci<int>()).name() << std::endl;
    for(; j <= 20; j++)
        std::cout << "Termino " << j << "-esimo: " << fibonacci<double>() << " " << typeid(fibonacci<double>()).name() << std::endl;

    /*
    Ok, falopeada que me llama la intencion. Dejando static unsigned long long int f1 = 0, f2 = 1;
    en la linea 26, yo esperaba que haga una unica secuencia y que segun lo que yo le ponga me devuelva
    un int o un double, pero parece que no funciona asi. Lo que hace son como dos funciones (y por lo tanto
    secuencias) distintas, y cada una tiene sus variables static particulares. No se, me hace ruido, porque
    de alguna forma lo entiendo como que son dos funciones distintas, que se diferencian por el tipo de 
    retorno. Como funciona asi, creo que es mas razonable poner como static variables tipo T.

    Si defino las variables static como globales, ahi si funciona como esperaba.
    */

    return 0;
}