/*
date: 28-09-2020
File: ej_07.cpp
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
#include <exception>


class Error_A{
public:
    Error_A (){}
    const char * what () const throw (){return "Error_A exception";}
};

class Error_B{
public:
    Error_B (){}
    const char * what () const throw (){return "Error_B exception";}
};

void func(){
    try{
        std::cout << "En func(), lanzo excepcion Error_B" << std::endl;
        throw Error_B();        
    }
    catch (const Error_A&e){
        std::cout << "Excepcion atrapada en func()" << std::endl;
        std::cout << "Tipo de excepcion: " << e.what() << std::endl;
    }
}

int main(int argc, const char** argv){
    
    try{
        std::cout << "En main(), llamo a func()" << std::endl;
        func();        
    }
    catch (const Error_B&e){
        std::cout << "Excepcion atrapada en main()" << std::endl;
        std::cout << "Tipo de excepcion: " << e.what() << std::endl;
    }

    return 0;
}