/*
date: 25-09-2020
File: ej_08.cpp
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

class A{
private:
public:
    int i;
    A(){}
    // A(int ii=0) : i(ii) {}
    virtual A* clone() = 0;
    // virtual ~A(){std::cout << "A::~A()" << std::endl;}
    virtual ~A(){}
    void setter(int ii){i = ii;}
    void print(){std::cout << i << std::endl;}
};


class B : public A{
public:
    B* clone() override;
    // ~B(){std::cout << "B::~B()" << this << std::endl;}
    ~B(){}
};

B* B::clone(){
    std::cout << "B::clone()" << std::endl;
    B *res = new B;
    res->setter(A::i);
    return res;
}

class C : public A{
public:
    C* clone() override;
    // ~C(){std::cout << "C::~C()" << this << std::endl;}
    ~C(){}
};

C* C::clone(){
    std::cout << "C::clone()" << std::endl;
    C *res = new C;
    res->setter(A::i);
    return res;
}

int main(int argc, const char** argv){

    A *aPtr;
    B b, *bPtr;
    C c, *cPtr;

    b.setter(42);
    c.setter(14);

    std::cout << "Llamo a clone() para clases derivadas, obteniendo punteros a clases derivadas" << std::endl;
    aPtr = b.clone();
    aPtr->print();
    bPtr = b.clone();
    bPtr->print();
    cPtr = c.clone();
    cPtr->print();
    delete aPtr;
    delete bPtr;
    delete cPtr;



    std::cout << "\nHago upcast para los tipos derivados y llamo a clone()" << std::endl;

    A* arr[] = {&b, &c};

    aPtr = arr[0]->clone();
    // bPtr = arr[0]->clone();    // Tira error: invalid conversion from ‘A*’ to ‘B*’
    aPtr->print();
    delete aPtr;

    aPtr = arr[1]->clone();
    aPtr->print();
    delete aPtr;


    std::cout << "\nPor ultimo, hago un dinamic_cast para poder obtener punteros a clases derivadas" << std::endl;
    bPtr = dynamic_cast<B*>(arr[0]->clone());
    bPtr->print();
    delete bPtr;


    return 0;
}