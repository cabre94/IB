/*
date: 28-08-2020
File: ej_10.cpp
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
    private:
        int a;
    public:
        A(int a_){a = a_;}
        void setArg(int a_){a = a_;}
        void print(){
            std::cout << a << std::endl;
        }
};