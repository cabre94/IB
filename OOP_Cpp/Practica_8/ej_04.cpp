/*
date: 19-09-2020
File: ej_04.cpp
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

class Roedor{
public:
    Roedor(){std::cout << "Roedor()\t" << this << std::endl;}
    ~Roedor(){std::cout << "~Roedor()\t" << this << std::endl;}
    virtual void tipo(){std::cout << "tipo: Roedor\t" << this << std::endl;}
};

class Raton: public Roedor{
public:
	Raton(){std::cout << "Raton()\t" << this << std::endl;}
	~Raton(){std::cout << "~Raton()\t" << this << std::endl;}
	void tipo() override {std::cout << "tipo: Raton\t" << this << std::endl;}
};

class Gerbo: public Roedor{
public:
	Gerbo(){std::cout << "Gerbo()\t" << this << std::endl;}
	~Gerbo(){std::cout << "~Gerbo()\t" << this << std::endl;}
	void tipo() override {std::cout << "tipo: Gerbo\t" << this << std::endl;}
};

class Hamster: public Roedor{
public:
	Hamster(){std::cout << "Hamster()\t" << this << std::endl;}
	~Hamster(){std::cout << "~Hamster()\t" << this << std::endl;}
	void tipo() override {std::cout << "tipo: Hamster\t" << this << std::endl;}
};

int main(int argc, const char** argv){
    
    std::vector<Roedor*> arr = {
        new Raton,
        new Gerbo,
        new Hamster
    };

    int i;
    for(i = 0; i < arr.size(); i++)
        arr[i]->tipo();
    
    for(i = 0; i < arr.size(); i++)
        delete arr[i];

    return 0;
}