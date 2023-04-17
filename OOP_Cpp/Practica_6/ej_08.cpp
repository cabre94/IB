/*
date: 14-09-2020
File: ej_8.cpp
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
    A(int i=0);
    A(const A &) = default;	//Copy constructor
    A(A &&) = default;	//Move constructor
    A &operator=(const A &) = default;	//Copy assignment
    A &operator=(A &&) = default;	// Move assignment
    // ~A(){delete ptr;}
    ~A(){}  // Lo correcto es hacer el delete pero si lo hago tira
            // un free(): double free detected

    void printPtr();
};

A::A(int i) : ptr(new int){
    *ptr = i;
}

void A::printPtr(){
    std::cout << ptr << std::endl;
}



class B{
private:
    int *ptr;    
public:
    B(int i=0);	//Default constructor
    B(const B &);	//Copy constructor
    B(B &&);	//Move constructor
    B &operator=(const B &);	//Copy assignment
    B &operator=(B &&);	// Move assignment
    ~B(){delete ptr;}

    void printPtr();
};

B::B(int i) : ptr(new int){
    *ptr = i;
}

B::B(const B &b) : ptr(new int){
    *ptr = *(b.ptr);
}

B &B::operator=(const B &b){
    if(&b != this){
        int *aux = new int;
        *aux = *(b.ptr);
        delete ptr;
        ptr = aux;
    }
    return *this;
}

B::B(B &&a) : ptr(a.ptr){
    a.ptr = nullptr;
}

B &B::operator=(B &&a){
    delete ptr;
    ptr = a.ptr;
    a.ptr = nullptr;
    return *this;
}

void B::printPtr(){
    std::cout << ptr << std::endl;
}


int main(int argc, const char** argv){

    std::cout << "Para la clase A (operator= por default)," <<
                 " los punteros de cada objeto son" << std::endl;
    
    A a1(14), a2(69);

    a1.printPtr();
    a2.printPtr();

    std::cout << "y luego de igualarlos, los punteros quedan" << std::endl;

    a2 = a1;

    a1.printPtr();
    a2.printPtr();


    std::cout << std::endl << "Para la clase B (operator= por default)," <<
                 " los punteros de cada objeto son" << std::endl;
    
    B b1(14), b2(69);

    b1.printPtr();
    b2.printPtr();

    std::cout << "y luego de igualarlos, los punteros quedan" << std::endl;

    b2 = b1;

    b1.printPtr();
    b2.printPtr();

    return 0;
}