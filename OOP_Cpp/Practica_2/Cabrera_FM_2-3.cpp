/*
date: 24-08-2020
File: ej_3.cpp
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

#define MAX_SIZE 10000

template <class T>
class Stack{
    T *v;
    int max_size, top;
public:
    class Underflow {};
    class Overflow {};
    class Bad_size {};
    
    Stack(int size);
    ~Stack();

    void push(T);
    T pop();
    int getTop(){return top;}

    // Sobrecargo <<. Es posible que para tipos de datos 'raros' falle.
    template<class H>
    friend std::ostream& operator<<(std::ostream &out, Stack<H> &s);
};

template<class T>
Stack<T>::Stack(int size){
    if(size > MAX_SIZE)
        throw Bad_size{};
    max_size = size;
    top = 0;
    v = new T[size];
}

template<class T>
Stack<T>::~Stack(){
    delete [] v;
}

template<class T>
void Stack<T>::push(T t){
    if(top == max_size)
        throw Overflow{};
    v[top++] = t;
}

template<class T>
T Stack<T>::pop(){
    if(top == 0)
        throw Underflow{};
    return v[--top];
}

template<class U>
//std::ostream& operator<<(ostream &out, Stack &s);
std::ostream& operator<<(std::ostream &out, Stack<U> &s){
    if(s.top == 0){
        out << "Stack is Empty";
    }else{
        int i;
        for(i=0; i < s.top-1; i++)
            out << s.v[i] << " -> ";
        out << s.v[i];
    }
    return out;
}


int main(int argc, const char** argv) {

    std::cout << "Creo un stack y lo imprimo:" << std::endl;

    Stack<int> s(100);
    std::cout << s << std::endl;

    srand(time(NULL));

    std::cout << "Meto algunos valores al azar e imprimo el Stack:" << std::endl;
    for(int i=0; i < 10; i++)
        s.push(rand() % 100);
    std::cout << s << std::endl;

    std::cout << "Saco un par de valores:" << std::endl;
    for(int i=0; i<5; i++)
        std::cout << "Saco: " << s.pop() << std::endl;
    
    std::cout << "Imprimo lo que quedo en el Stack:" << std::endl;
    std::cout << s << std::endl;

    return 0;
}