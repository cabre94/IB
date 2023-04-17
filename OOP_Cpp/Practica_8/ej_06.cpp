/*
date: 19-09-2020
File: ej_06.cpp
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
    int i;

public:
    uintptr_t *vptr;
    A(int ii = 0) : i(ii) {std::cout << "A::A() @ " << this << std::endl;}
    virtual void func1(){std::cout << "A::func1() i = " << i << " @ " << this << std::endl;}
    virtual void func2(){std::cout << "A::func2() i = " << i << " @ " << this << std::endl;}
};

// class A1 : public A{
// public:
//     void func1() override{std::cout << "A1::func1() @ " << this << std::endl;}
// };

// class A2 : public A{
// public:
//     void func2() override{std::cout << "A2::func2() @ " << this << std::endl;}
// };


int main(int argc, const char** argv){

    A a1;
    // A *aptr = &a1;

    std::cout << a1.vptr << std::endl;
    // std::cout << a1.func1() << std::endl;
    // std::cout << a1.func2() << std::endl;
    std::cout << &a1 << std::endl;
    


    return 0;
}