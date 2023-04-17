/*
date: 15-09-2020
File: ej_02.cpp
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

class Counted{
private:
    int id;
    static int count;
public:
    Counted() : id(count++){std::cout << "Constructor id = " << id << std::endl;}
    ~Counted(){std::cout << "Destructor id = " << id << std::endl;}
};

int Counted::count = 0;

int main(int argc, const char** argv){

    std::cout << "Usando new y delete:" << std::endl;

    Counted *ptr = new Counted[5];
    delete [] ptr;

    std::cout << std::endl << "Ahora pruebo con arreglos:" << std::endl;

    Counted arr[5];
    
    return 0;
}