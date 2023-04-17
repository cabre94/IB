/*
date: 27-08-2020
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

class Messege{
private:
    std::string str;
public:
    Messege(std::string);
    void print();
    void print(std::string);
    //void print(std::string str1=""); //Creo que la idea es ver que seria mejor hacer algo como esto
};

Messege::Messege(std::string str_="KK"){
    str = str_;
}

void Messege::print(){
    std::cout << str << std::endl;
}

void Messege::print(std::string str1){
    std::cout << str + str1 << std::endl;
}

// Creo que la idea es ver que seria mejor hacer algo como esto
/*
void Messege::print(std::string str1=""){
    std::cout << str + str1 << std::endl;
}
*/

int main(int argc, const char** argv) {
    Messege s;
    s.print();
    s.print(" y +KK");
    return 0;
}