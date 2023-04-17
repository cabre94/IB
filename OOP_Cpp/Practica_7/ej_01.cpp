/*
date: 15-09-2020
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
   
    for(int i=0; i<10; i++)
        Counted x;
    
    std::cout << std::endl << "Despues del loop:" << std::endl;
    
    Counted a;
    Counted b;

    return 0;
}