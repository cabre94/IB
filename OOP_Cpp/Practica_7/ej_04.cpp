/*
date: 15-09-2020
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

    Counted *ptr = new Counted[5];

    delete ptr;

    /*
    https://stackoverflow.com/questions/2425728/delete-vs-delete-operators-in-c

    Creo que la idea es que delete libera la memoria y llama al constructor para un
    solo objeto, mientras que delete [] lo hace para cada elemento del array.
    No se si hay que decir mucho mas que eso.
    */
    
    return 0;
}