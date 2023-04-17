/*
date: 12-09-2020
File: ej_7.cpp
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
    int member;    
public:
    A(int member_=0);	//Default constructor
    A(const A &);	//Copy constructor
    A(A &&);	//Move constructor
    A &operator=(const A &) = default;	//Copy assignment
    A &operator=(A &&) = default;	// Move assignment
    ~A();

    A operator+(A a_);
};

A::A(int member_): member{member_}{
    std::cout << "Constructor de A " << this << std::endl;
}

A::A(const A &a_) : member{a_.member}{
    std::cout << "Copy constructor de A " << this << std::endl;
}

A::A(A &&a_): member{a_.member}{
    std::cout << "Move constructor de A" << this << std::endl;
}

A::~A(){
    std::cout << "Destructor de A" << this << std::endl;
}

A A::operator+(A a_){
    A res(member+a_.member);
    return res;
}


A f(){
    A res(42);
    return res;
}


int main(int argc, const char** argv){

    A kk(2);
    A kk2;

    kk2 = f();

    kk2 = kk + kk;

    // Compilar con g++ -fno-elide-constructors ej_7.cpp -o exe
    
    return 0;
}