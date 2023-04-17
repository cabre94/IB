/*
date: 27-08-2020
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

class A{
public:
    A(){
        std::cout << "Creo objeto A" << std::endl;
    }
};

class B{
private:
    A a;
public:
    B(){
        std::cout << "Creo objeto B" << std::endl;
    }
};


int main(int argc, const char** argv) {

    B b[5];
    return 0;
}