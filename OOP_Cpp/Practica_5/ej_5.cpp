/*
date: 12-09-2020
File: ej_5.cpp
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
private:
    
public:
    A();	//Default constructor
    A(const A &);	//Copy constructor
    A(A &&) = default;	//Move constructor
    A &operator=(const A &) = default;	//Copy assignment
    A &operator=(A &&) = default;	// Move assignment
    ~A();
};

A::A(){
    std::cout << "Constructor de A " << this << std::endl;
}

A::A(const A &){
    std::cout << "Copy constructor de A " << this << std::endl;
}

A::~A(){
    std::cout << "Destructor de A " << this << std::endl;
}

class B{
private:
    A a;
    int c;
public:
    B();	//Default constructor
    B(const B &) = default;	//Copy constructor
    B(B &&) = default;	//Move constructor
    B &operator=(const B &) = default;	//Copy assignment
    B &operator=(B &&) = default;	// Move assignment
    ~B();
};

B::B(){
    std::cout << "Constructor de B " << this << std::endl;
}

B::~B(){
    std::cout << "Destructor de B " << this << std::endl;
}

void f(B b){
    std::cout << "Cuerpo de f()..." << std::endl;
}


int main(int argc, const char** argv){
    
    B kk;
    A kk2;

    f(kk);


    return 0;
}