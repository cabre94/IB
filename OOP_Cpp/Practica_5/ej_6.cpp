/*
date: 12-09-2020
File: ej_6.cpp
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

A::A(const A &a){
    std::cout << "Copy constructor de A " << this << std::endl;
}

A::~A(){
    std::cout << "Destructor de A " << this << std::endl;
}


class B{
private:
    
public:
    B();	//Default constructor
    B(const B &);	//Copy constructor
    B(B &&) = default;	//Move constructor
    B &operator=(const B &) = default;	//Copy assignment
    B &operator=(B &&) = default;	// Move assignment
    ~B();
};

B::B(){
    std::cout << "Constructor de B " << this << std::endl;
}

B::B(const B &b){
    std::cout << "Copy constructor de B " << this << std::endl;
}

B::~B(){
    std::cout << "Destructor de B " << this << std::endl;
}


class C{
private:
    A a;
    B b;
public:
    C();	//Default constructor
    C(const C &);	//Copy constructor
    C(C &&) = default;	//Move constructor
    C &operator=(const C &) = default;	//Copy assignment
    C &operator=(C &&) = default;	// Move assignment
    ~C();
};

C::C(){
    std::cout << "Constructor de C " << this << std::endl;
}

C::C(const C &c): a{c.a}, b(c.b) {
    std::cout << "Copy constructor de C " << this << std::endl;
}

C::~C(){
    std::cout << "Destructor de C " << this << std::endl;
}




int main(int argc, const char** argv){

    C c;

    C c2 = c;

    return 0;
}