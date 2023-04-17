/*
date: 26-09-2020
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

template<class T>
class List{
private:

public:
    T data;
    List<T> *pNext;

    List(T data_) : data(data_) {pNext = nullptr;}
    // List(T data_) : data(data_), pNext(nullptr) {}
    // List(){}
    void add(T data_);

    template <class U>
    friend std::ostream& operator<<(std::ostream &out, List<U> &l);
    
};

template<class T>
void List<T>::add(T data_){
    List<T> *pList = new List<T>(data_);
    List<T> *pAux = pNext;
    // List<T> *pAux = this;
    
    std::cout << pAux << std::endl;
    while(pAux != nullptr){
        pAux = pAux->pNext;
        std::cout << pAux << std::endl;
    }

    pAux = pList;
    std::cout << "En add()  " << pAux << std::endl;
}

template<class T>
std::ostream& operator<<(std::ostream &out, List<T> &l){
    out << l.data << " -> ";
    List<T> *pAux = l.pNext;

    while(pAux != nullptr){
        out << pAux->data << " -> ";
        pAux = pAux->pNext;

    }

    return out;
}


int main(int argc, const char** argv){
    
    List<int> list(0);

    std::cout << "Agrego un 1" << std::endl;
    list.add(1);
    std::cout << "En main() " << list.pNext << std::endl;

    // std::cout << "\nAgrego un 2" << std::endl;
    // list.add(2);

    // for(int i=1; i <= 10; i++){
    //     list.add(i);
    //     // std::cout << "Agrego " << i << std::endl;
    // }
    
    // std::cout << "Hasta aca todo bien" << std::endl;
    // std::cout << list.data << std::endl;
    // std::cout << list.pNext->data << std::endl;
    
    // std::cout << list << std::endl;

    return 0;
}