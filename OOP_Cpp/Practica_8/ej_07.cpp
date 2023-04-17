/*
date: 25-09-2020
File: ej_07.cpp
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
};

class B : public A{
    int j;
};

void func(A a){
    std::cout << "En func() sizeof = " << sizeof(a) << std::endl;
}

int main(int argc, const char** argv){
    
    B b;

    std::cout << "En main() sizeof = " << sizeof(b) << std::endl;
    func(b);

    /*
    Tengo que repasar la teoria, pero habia algo que pasaba que cortaba
    la informacion a la del tipo de dato cuando se pasaba por copia, o
    algo asi.
    */

    return 0;
}
