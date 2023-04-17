/*
date: 23-08-2020
File: ej_1.cpp
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
#include <cstdlib>          // Esta creo que es para el qsort

struct Persona{
    char nombre[64];
    char apellido[64];
    int dni;
    char calle[64];
    int numero;
    int cPostal;
    char fNacimiento[64];
};

// Ingresa los datos de una persona
void ingresaPersona(Persona *pPers){
    std::cout << "Ingresar datos de la persona" << std::endl;

    std::cout << "Nombre: ";
    std::cin >> pPers->nombre;
    
    std::cout << "Apellido: ";
    std::cin >> pPers->apellido;
    
    std::cout << "DNI: ";
    std::cin >> pPers->dni;

    std::cout << "Calle: ";
    std::cin >> pPers->calle;

    std::cout << "Numero ";
    std::cin >> pPers->numero;

    std::cout << "Codigo postal: ";
    std::cin >> pPers->cPostal;

    std::cout << "Fecha de Nacimiento: " << std::endl;
    std::cin >> pPers->fNacimiento;
    std::cout << std::endl;
}

// Imprime persona
void imprimePersona(Persona *pPers){
    std::cout << "Nombre: " << pPers->nombre << std::endl;
    std::cout << "Apellido: " << pPers->apellido << std::endl;
    std::cout << "DNI: " << pPers->dni << std::endl;
    std::cout << "Domicilio: " << pPers->calle << " " << pPers->numero << std::endl;
    std::cout << "C.P.: " << pPers->cPostal << std::endl;
    std::cout << "Fecha de nacimiento: " << pPers->fNacimiento << std::endl << std::endl;
}

typedef int (FunCmp_t)(const Persona *, const Persona *);

int comparaPorDNI(const Persona *pa, const Persona *pb){
    return pa->dni - pb->dni;
}

/*
int cmpApellido(const Persona *pa, const Persona *pb){
    return pa->apellido.compare(pb->apellido);
}
*/

int CompareStrings(const char *str1, const char *str2){
    while((*str1)||(*str2)){
        if (*str1>*str2)
            return 1;
        if (*str1<*str2)
            return -1;
        str1++;
        str2++;
    }
    return 0;
}


int cmpApellido(const Persona *pa, const Persona *pb){
    return CompareStrings(pa->apellido, pb->apellido);
}




void ordenaPersona(Persona *pPersonas, int cnt, FunCmp_t fc){
    typedef int (*qsortCmp_t)(const void *, const void *);  // Esto fue magia de Tapia
    qsort(pPersonas, cnt, sizeof(Persona),(qsortCmp_t) fc);
}


int main(int argc, const char** argv) {

    Persona personas[3];

    for (int i = 0; i < 3; i++){
        ingresaPersona(&personas[i]);
    }

    ordenaPersona(personas, 3, cmpApellido);
    //qsort(personas, 3, sizeof(Persona), comparaPorDNI);

    std::cout << "Despues de ordenarlo" << std::endl;
    for (int i = 0; i < 3; i++){
        imprimePersona(&personas[i]);
    }

    return 0;
}