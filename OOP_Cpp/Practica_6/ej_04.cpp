/*
date: 13-09-2020
File: ej_4.cpp
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
    A(){}
    ~A();
};

A::~A(){
    std::cout << "Destructor..." << std::endl;
    exit(1);
}

A a;

int main(int argc, const char** argv){    
    return 0;
}