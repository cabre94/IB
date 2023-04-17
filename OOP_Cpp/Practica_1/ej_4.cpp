/*
date: 23-08-2020
File: ej_4.cpp
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
    char c;
    int count = 0;
    bool space = false;

    while ( (c=std::cin.get()) != EOF){
        if(c == '(')
            count++;
        else if(c == ')')
            count--;
        else if(count == 0)
            if(c == ' ' && !space){
                std::cout.put(c);
                space = true;
            }else if(c != ' '){
                std::cout.put(c);
                space = false;
            }
    }    

    return 0;
}
