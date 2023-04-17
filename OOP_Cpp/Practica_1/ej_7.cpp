/*
date: 23-08-2020
File: ej_7.cpp
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

void left_trim(char phrase[]){
    int i=0, j=0;
    bool space = true;
    while(phrase[i]){
        if(phrase[i] != ' '){
            phrase[j] = phrase[i];
            j++;
            space = false;
        }else if(!space){
            phrase[j] = phrase[i];
            j++;
            space = true;
        }
        i++;
    }
    phrase[j] = 0;
}

int main(){
	char s[64] = "    Joaco   se  lastra      ";
	left_trim(s);
	std::cout << s << std::endl;
	return 0;
}