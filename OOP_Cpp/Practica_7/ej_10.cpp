/*
date: 16-09-2020
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

class Z{
public:
    Z(){std::cout << "Z" << std::endl;}
    ~Z(){std::cout << "~Z" << std::endl;}
};

class A{
public:
    A(){std::cout << "A" << std::endl;}
    ~A(){std::cout << "~A" << std::endl;}
};

class B : public A{
private:
    Z z;
public:
    B(){std::cout << "B" << std::endl;}
    ~B(){std::cout << "~B" << std::endl;}
};

class C : public B{
public:
    C(){std::cout << "C" << std::endl;}
    ~C(){std::cout << "~C" << std::endl;}
};


int main(int argc, const char** argv){
    C c;
    return 0;
}