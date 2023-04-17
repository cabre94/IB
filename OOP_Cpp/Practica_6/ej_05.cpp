/*
date: 13-09-2020
File: ej_5.cpp
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

#include "ej_05.h"

void func(){
    std::cout << "En func() valor antes de ser modificado: " << local << std::endl;
    local = 1;
    std::cout << "En func() valor despues de ser modificado: " << local << std::endl;
}

