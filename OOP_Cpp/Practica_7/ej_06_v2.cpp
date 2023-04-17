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
    std::vector<int> *p = new std::vector<int>(1024);
    static int count = 1024;
    //char *p;
    try{
        while(true){
            //new char[10000]; // Esto son 10000 bytes?
            //for(int i=0; i<1024; i++)   
            //p = new char[1024]; // Esto son 1 kilobytes?
            p = new std::vector<int>(1024);
            (*p)[0] = 1;
            // p[0] = 'x';
            count += 1024;
            //std::cout << count * sizeof(p) << std::endl;
        }
    }
    // catch (...){
    catch (std::bad_alloc){
        std::cout << "Memoria total: " << count * sizeof(p) << std::endl;
    }
}

int main(int argc, const char** argv){
    
    f();

    return 0;
}