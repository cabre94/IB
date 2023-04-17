/*
date: 12-09-2020
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
#include <cstdlib>

class A{
private:
    int *ptr;    
public:
    A(int a_=69);	//Default constructor
    A(const A &) = default;	//Copy constructor
    A(A &&) = default;	//Move constructor
    //A &operator=(const A &) = default;	//Copy assignment
    A &operator=(const A &);	//Copy assignment
    A &operator=(A &&) = default;	// Move assignment
    ~A();

    void printPtr();
};

A::A(int a_){
    ptr = new int;
    *ptr = a_;
}

A::~A(){
    delete ptr;
}

void A::printPtr(){
    std::cout << "Un puntero es " << ptr << std::endl;
}

// Para que todo ande bien, hay que implementar esto
A &A::operator=(const A &a){
    int *p = new int;
    *p = *a.ptr;
    delete ptr;
    ptr = p;
    return *this;
}

int main(int argc, const char** argv){
    
    A kk1(85), kk2;

    kk2 = kk1;

    kk1.printPtr();
    kk2.printPtr();

    return 0;
}