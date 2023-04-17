/*
date: 15-09-2020
File: ej_05.cpp
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

    Counted *ptr = new Counted;

    //void* vptr = (void*) ptr;
    
    // delete vptr;
    delete ptr; // Lo pongo bien porque el VSCode me lo deja en color si esta mal y me molesta

    /*
    Parece que el efecto es que no se esta llamando al destructor del objeto a donde apunta el objeto.
    Supongo que el tipo de puntero le dice de alguna forma a que destructor debe llamar (lo cual parece
    razonable ya que si es void en principio podria ser cualquer caca)
    */

    return 0;
}