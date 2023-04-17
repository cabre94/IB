/*
date: 13-09-2020
File: ej_3.cpp
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


class Monitor{
private:
    int counter;

public:
    Monitor(int c=0) : counter(c){};
    void incident();
    void print();

};


void Monitor::incident(){
    counter++;
}

void Monitor::print(){
    std::cout << "Numero de llamadas " << counter << std::endl;
}

void func(){
    static Monitor m;

    m.incident();
    m.print();
}

int main(int argc, const char** argv){
    
    for(int i=0; i < 20; i++)
        func();

    return 0;
}