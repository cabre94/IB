/*
date: 28-09-2020
File: ej_10.cpp
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


class Error_A : public std::runtime_error{
public:
    Error_A () : std::runtime_error("") {}
    const char * what () const throw (){return "runtime_error::Error_A exception";}
};

class Error_B : public std::runtime_error{
public:
    Error_B () : std::runtime_error("") {}
    const char * what () const throw (){return "runtime_error::Error_B exception";}
};

class Error_C : public std::runtime_error{
public:
    Error_C () : std::runtime_error("") {}
    const char * what () const throw (){return "runtime_error::Error_C exception";}
};



int main(int argc, const char** argv){
    
    try{
        throw Error_C();
        throw Error_A();
        throw Error_B();        
    }catch (const Error_B&e){
        std::cout << "Excepcion atrapada en Catch Error_B" << std::endl;
        std::cout << "Tipo de excepcion: " <<e.what() << std::endl;
    }catch (const std::runtime_error& e){
        std::cout << "Excepcion atrapada en Catch Base" << std::endl;
        std::cout << "Tipo de excepcion: " << e.what() << std::endl;
    }

    return 0;
}