/*
date: 12-09-2020
File: ej_1.cpp
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
    A();
    A(A &&) = default;
    A(const A &) = default;
    A &operator=(A &&) = default;
    A &operator=(const A &) = default;
    ~A();

private:
    
};

A::A(){
}

A::~A(){
}