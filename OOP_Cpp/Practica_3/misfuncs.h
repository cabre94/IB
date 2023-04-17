#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <array>
#include <vector>
#include <algorithm>


// Funciones del ejercicio 3 de la practica 1
void printDigit(int num);
void deBase10A(int num, int b);

/*
Otras funciones
*/

// Implementacion de Stack del ejercicio 3 de la practica 2

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

    // Sobrecargo <<. Es posible que para tipos de datos 'raros' falle.
    template<class H>
    friend std::ostream& operator<<(std::ostream &out, Stack<H> &s);
};

#define STACK_MAX_SIZE 10000

template<class T>
Stack<T>::Stack(int size){
    if(size > STACK_MAX_SIZE)
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