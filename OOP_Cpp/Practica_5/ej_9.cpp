/*
date: 12-09-2020
File: ej_9.cpp
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

class B{
private:
    int bMember;
public:
    B(int bMember_): bMember{bMember_}{};	//Ordinary constructor
    ~B(){};
};

class C{
private:
    int cMember;    
public:
    C(int cMember_): cMember{cMember_}{};	//Ordinary constructor
    ~C(){};
};


class A{
private:
    B b;
    C c;
public:
    A(int bMember=0, int cMember=0);	//Default constructor
    ~A(){};
};

// Esta no funciona
/*
A::A(int bMember, int cMember){
}
*/

// Si no me equivoco, la razon es que al llamar al constructor de A sin la inicialization list, primero
// llama a los constructores por defecto de b y c, que, al no tenerlos, explota.
// Al usar la initialization list, se llaman a los constructores correspondientes y ahi si funca.
A::A(int bMember, int cMember) : b{bMember}, c{cMember}{
}




int main(int argc, const char** argv){
    
    A a();

    return 0;
}