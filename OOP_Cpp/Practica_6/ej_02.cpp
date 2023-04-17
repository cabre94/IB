/*
date: 13-09-2020
File: ej_2.cpp
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






int func(int *arg=0){

    static int *ptr;

    if(arg)
        ptr = arg;
    if(*ptr != -1)
        return *ptr++;
    return -1;
}

int main() {
    
    int v[]{1, 3, 5, 7, -1};
    int x = func(v);

    do{
        std::cout << x << std::endl;
        x = func();
    }while(x != -1);

    return 0;
}