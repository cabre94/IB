/*
date: 15-09-2020
File: ej_12.cpp
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
    int i;
public:
    A(int ii=0) : i(ii){}

    A operator+(const A &a){return A(i+a.i);}
    A operator-(const A &right){return A(i-right.i);}

    A &operator++();
    A operator++(int);
    A &operator--();
    A operator--(int);

    std::ostream &print(std::ostream &out){return out << i;}
    //void print(std::ostream &out){out << i;}  // Algo equivalente

    // Esto es mas lindo, pero piden una funcion miembro
    //friend std::ostream& operator<<(std::ostream &out, const A &n){return out << n.i;}
};

A &A::operator++(){
    i++;
    return *this;
}

A A::operator++(int){
    A before(i);
    i++;
    return before;
}

A &A::operator--(){
    i--;
    return *this;
}

A A::operator--(int){
    A before(i);
    i--;
    return before;
}


int main(int argc, const char** argv){
    A kk1(14), kk2(69), kk3(42);

    (kk1+kk2-kk3).print(std::cout);
    std::cout << std::endl;

    (kk1++).print(std::cout);
    std::cout << std::endl;

    (++kk1).print(std::cout);
    std::cout << std::endl;

    (kk1--).print(std::cout);
    std::cout << std::endl;

    (--kk1).print(std::cout);
    std::cout << std::endl;
    return 0;
}