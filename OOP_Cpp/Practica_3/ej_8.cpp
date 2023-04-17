/*
date: 26-08-2020
File: ej_8.cpp
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
    char *p = "ojo";    // Esto tira warning
    char q[] = "chau";
    const char *r = "hola";

    // p[2] = 'k';  Esto asi explota
    q[2] = 'k';
    // r[2] = 'k';      Esto explota, y creo que esta bien

    std::cout << p << std::endl;
    std::cout << q << std::endl;
    std::cout << r << std::endl;
    
    return 0;
}