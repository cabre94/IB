/*
date: 16-09-2020
File: ej_08.cpp
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



class A{
private:
    static const int MAX = 5;
    static int n;

public:
    A();
    ~A();

    A(const A &) = delete;	//Copy constructor
    A(A &&) = delete;	    //Move constructor
    A &operator=(const A &) = delete;	//Copy assignment
    A &operator=(A &&) = delete;	    // Move assignment

    void* operator new(size_t);
    void  operator delete(void*);
    
    void* operator new[](size_t) = delete;
    void  operator delete[](void*) = delete;
    
    void* operator new(size_t, const std::nothrow_t&) = delete;
    void* operator new[](size_t, const std::nothrow_t&) = delete;
    void  operator delete(void*, const std::nothrow_t&) = delete;
    void  operator delete[](void*, const std::nothrow_t&) = delete;
    
    void* operator new(size_t, void* ) = delete;
    void* operator new[](size_t, void*) = delete;
    void  operator delete(void*, void*) = delete;
    void  operator delete[](void*, void*) = delete;
};

int A::n = 0;

A::A(){
    n++;
    std::cout << "A() "<< this << std::endl;
}

A::~A(){
    n--;
    std::cout << "~A() " << this << std::endl;
}

void* A::operator new(size_t sz){
    if(n >= MAX){
        std::cout << "Bad alloc: ";
        throw std::bad_alloc{};
    }else{
        void *m = malloc(sz);
        std::cout << "Alloco memoria " << m << std::endl;
        return m;
    }
}

void  A::operator delete(void* m){
    if(!n)
        return;
    std::cout << "Destruyendo memoria " << m << std::endl;
    free(m);
}


int main(int argc, const char** argv){
    A kk;
    A kk2;

    A *pptr[10];

    int i;
    
    try{
        for(i = 0; i < 10; i++)
            pptr[i] = new A;
    }
    catch (const std::bad_alloc){
        std::cout << "Supero la cantidad maxima de instancias" << std::endl;
    }

    while(i--)
        delete pptr[i];

    return 0;
}