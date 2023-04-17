/*
date: 13-09-2020
File: ej_6.cpp
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

class Integer{
private:
    int i;
public:
    Integer(int ii) : i{ii} {}

    Integer &operator++(){          // Prefijo
        i++;
        return *this;
    }
    Integer operator++(int dummy){  // Postfijo
        Integer before(i);
        i++;
        std::cout << dummy << std::endl;
        return before;
    }
    Integer &operator--(){
        i--;
        return *this;
    }
    Integer operator--(int dummy){
        Integer before(i);
        i--;
        std::cout << dummy << std::endl;
        return before;
    }
};


int main(int argc, const char** argv){
    
    Integer kk(42);

    kk++;

    ++kk;

    kk--;

    --kk;

    return 0;
}