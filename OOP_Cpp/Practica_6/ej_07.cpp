/*
date: 13-09-2020
File: ej_7.cpp
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

class Number{
private:
    double x;    
public:
    Number(double x_=0) : x{x_} {}	//Default constructor
    Number(const Number &) = default;	//Copy constructor
    Number(Number &&n) :x{n.x} {};	//Move constructor
    Number &operator=(const Number &);	//Copy assignment
    Number &operator=(Number &&);	// Move assignment
    ~Number(){};

    Number operator+(const Number &n){return Number(x+n.x);}
    Number operator-(const Number &n){return Number(x-n.x);}
    Number operator-(){return Number(-x);}
    Number operator*(const Number &n){return Number(x*n.x);}
    Number operator/(const Number &n){return Number(x/n.x);}

    operator double() const {return double(x);}

    friend std::ostream& operator<<(std::ostream &out, const Number &n){return out << n.x;}
};


Number &Number::operator=(const Number &n){
    if(&n != this)
        x = n.x;
    return *this;
}

Number &Number::operator=(Number &&n){
    x = n.x;
    return *this;
}

void func(double x){
    std::cout << "En func(): " << x << std::endl;
}


int main(int argc, const char** argv){
    Number kk1(3), kk2(4), kk3(5), kk4;

    kk4 = kk1 + kk2 + kk3;

    std::cout << kk4 << std::endl;

    kk4 = -kk1 - kk2 - kk3;

    std::cout << kk4 << std::endl;
    std::cout << kk1 + kk2 << std::endl;

    func(kk1);

    return 0;
}