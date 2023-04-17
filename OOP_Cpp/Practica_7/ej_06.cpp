/*
date: 15-09-2020
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
#include <cstdlib>
#include <exception>


void f(){
    static int count = 0;   // Megas?
    int *p;
    try{
        for(;;){
            //new char[10000]; // Esto son 10000 bytes?
            //for(int i=0; i<1024; i++)   
            p = new int[1024]; // Esto son 1 kilobytes?
            p[0] = 1;
            count += 1024;
            //std::cout << count * sizeof(p) << std::endl;
        }
    }
    catch (std::bad_alloc){
        std::cout << count * sizeof(p) << std::endl;
    }
}

int main(int argc, const char** argv){
    
    f();

    return 0;
}