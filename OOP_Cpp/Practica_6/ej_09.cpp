/*
date: 15-09-2020
File: ej_9.cpp
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

class Orange{
public:
    Orange(){}

    friend std::ostream& operator<<(std::ostream &out, const Orange &n);
};

class Apple{
public:
    Apple (Orange){}

    friend std::ostream& operator<<(std::ostream &out, const Apple &n);
};


std::ostream& operator<<(std::ostream &out, const Orange &n){
    return out << "Esto es un Orange";
}

std::ostream& operator<<(std::ostream &out, const Apple &n){
    return out << "Esto es un Apple";
}

void func(Apple a){
    std::cout << "En func() " << a << std::endl;
}


int main(int argc, const char** argv){
    Orange o;

    std::cout << "En main() " << o << std::endl;

    func(o);

    return 0;
}