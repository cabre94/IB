/*
date: 27-09-2020
File: ej_06.cpp
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
#include <memory>


template<class T>
class UniquePtr{
private:
    T* ptr;
    
public:
    UniquePtr(T *ptr_=nullptr);	        //Default constructor
    UniquePtr(UniquePtr &&);	        //Move constructor
    UniquePtr &operator=(UniquePtr &&);	// Move assignment

    UniquePtr(const UniquePtr &) = delete;	            //Copy constructor
    UniquePtr &operator=(const UniquePtr &) = delete;	//Copy assignment

    ~UniquePtr();
};

template<class T>
UniquePtr<T>::UniquePtr(T* ptr_) : ptr(ptr_) {
    std::cout << ptr <<" Constructed" << std::endl;
}

template<class T>
UniquePtr<T>::~UniquePtr(){
    std::cout << "Deleting " << ptr << std::endl;
    delete ptr;
}

template<class T>
UniquePtr<T>::UniquePtr(UniquePtr<T> &&uPtr) : ptr( std::move(uPtr.ptr) ) {
    std::cout << "Move Constructor " << ptr << std::endl;
    uPtr.ptr = nullptr;
}

template<class T>
UniquePtr<T> &UniquePtr<T>::operator=(UniquePtr &&uPtr){
    if(this != &uPtr){
        ptr = std::move(uPtr.ptr);          // Capaz seria mejor definir la swap
        uPtr.ptr = nullptr;
        std::cout << "Move assigment " << ptr << std::endl;
    }
    return *this;
}



int main(int argc, const char** argv){

    UniquePtr<double> up;           // Le deberia asignar un nullptr
    UniquePtr<int> up1(new int);

    UniquePtr<int> up2 = std::move(up1);
    // UniquePtr<int> up3 = up1;    // Error

    up1 = std::move(up2);
    // up1 = up2;   // Error


    // Ahora usamos el std::unique_ptr
    std::unique_ptr<double> u_p;
    std::unique_ptr<int> u_p1(new int);

    std::unique_ptr<int> u_p2 = std::move(u_p1);
    // std::unique_ptr<int> u_p3 = u_p1;    // Error

    u_p1 = std::move(u_p2);
    // u_p1 = u_p2;         // Error

    return 0;
}