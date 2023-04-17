/*
date: 27-08-2020
File: ej_4.cpp
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

class Date{
private:
    int dia, mes, ano;
public:
    void setDia(int d){dia = d;}
    void setMes(int m){mes = m;}
    void setAno(int n){ano = n;}
    int getDia(){return dia;}
    int getMes(){return mes;}
    int getAno(){return ano;}
};