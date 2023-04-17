/*
date: 25-08-2020
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

int main(int argc, const char** argv) {
    
    double arr1[10] = {1, 2, 3, 4, 5};

    double arr2[] = {1,2,3,4,5};

    int size1 = sizeof(arr1)/sizeof(double);
    std::cout << "Tamaño del primer arreglo: " << size1 << std::endl;
    for(int i=0; i<size1; i++)
        std::cout << arr1[i] << std::endl;

    int size2 = sizeof(arr2)/sizeof(double);
    std::cout << "Tamaño del segundo arreglo: " << size2 << std::endl;
    for(int i=0; i<size2; i++)
        std::cout << arr2[i] << std::endl;
    
    return 0;
}