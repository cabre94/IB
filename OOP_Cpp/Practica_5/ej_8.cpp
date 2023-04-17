/*
date: 12-09-2020
File: ej_8.cpp
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

class Manager{
private:
    int member;
    static Manager* sManager;
    
    Manager(int member_=69): member{member_}{};    
    Manager(const Manager &) = default;	//Copy constructor
    Manager(Manager &&) = default;	//Move constructor
    Manager &operator=(const Manager &) = default;	//Copy assignment
    Manager &operator=(Manager &&) = default;	// Move assignment
    ~Manager();

public:
    static Manager *getInstance();

    void setMember(int member_){member = member_;}

    void check();
};

Manager* Manager::sManager = nullptr; // Para vers anteriores a C++17, no?

Manager *Manager::getInstance(){
    if(sManager == nullptr)
        sManager = new Manager;
    return sManager;
}

void Manager::check(){
    std::cout << "Direccion de memoria: " << this;
    std::cout << " Valor = " << member << std::endl;
}

// Los ejemplos que vi en internet no liberan la memoria, me hace ruido
Manager::~Manager(){
    if(sManager != nullptr)
        delete sManager;
    sManager = nullptr;
}


int main(int argc, const char** argv){

    // Manager kk;  // Explota
    // Manager *kk;    // Explota

    std::cout << "Instancio" << std::endl;
    
    Manager *m = Manager::getInstance();
    m->check();
    m->setMember(14);

    std::cout << "Instancio una segunda vez" << std::endl;
    Manager *m2 = Manager::getInstance();
    m2->check();

    return 0;
}

