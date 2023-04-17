#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <array>
#include <vector>
#include <algorithm>

void printDigit(int num){
    if(num < 10)
        std::cout << num;
    else
        std::cout << (char) ('A'+num-10);
}

void deBase10A(int num, int b){
    if (num >= b)
        deBase10A(num/b, b);
    printDigit(num % b);
}