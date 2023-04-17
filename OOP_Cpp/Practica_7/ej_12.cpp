/*
date: 16-09-2020
File: ej_12.cpp
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

class SpaceShip{
public:
    void fly(){std::cout << "SpaceShip volando..." << std::endl;}
    void land(){std::cout << "SpaceShip aterrizando" << std::endl;}
};

class Shuttle : public SpaceShip{
public:
    void land(){std::cout << "Shuttle aterrizando" << std::endl;}
};


int main(int argc, const char** argv){
    
    Shuttle s;

    SpaceShip *sPtr = &s;

    sPtr->land();
    s.land();

    /*
    Inicialmente la clase SpaceShip no tenia el metodo land(). Es este caso, el compilador tira
    error en sPtr->land() ya que al hacer el upcasting se pierde la informacion del metodo
    land() que solo esta en la clase Shuttle y solo se puede usar la interfaz de SpaceShip.

    Solamente para ver un poco mejor esto, le agregue el metodo land() a la clase SpaceShip
    para verificar que al hacer sPtr->land() se llama al metodo land() de SpaceShip y no de
    Shuttle.
    */

    return 0;
}