/*
date: 27-08-2020
File: ej_4.cpp
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
    int x;
};

/*
class A{
public:
    A(int x_){x = x_;}
    int x;
};
*/  // Tira no default constructor exists for class "A" ---> Mi editor
    // no matching function for call to ‘A::A()’ ---> Esto tira el compilador



int main(int argc, const char** argv) {

    A a;

    std::cout << a.x << std::endl;

    return 0;
}