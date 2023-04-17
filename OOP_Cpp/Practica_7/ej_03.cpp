/*
date: 15-09-2020
File: ej_03.cpp
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

class Counted{
private:
    static int count;
public:
    int id;
    Counted() : id(count++){std::cout << "Constructor id = " << id << std::endl;}
    ~Counted(){std::cout << "Destructor id = " << id << std::endl;}

    friend std::ostream& operator<<(std::ostream &out, const Counted &n){return out << n.id;}
};

int Counted::count = 0;

int main(int argc, const char** argv){

    std::vector<Counted*> v;

    for(int i=0; i<5; i++){
        Counted *ptr = new Counted;
        v.push_back(ptr);
    }

    for(int i=0; i<5; i++)
        std::cout << v[i] << " - id: " << *v[i] << std::endl;
    
    for(int i=0; i<5; i++)
        delete v[i];

    
    return 0;
}