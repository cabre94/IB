/*
date: 23-08-2020
File: ej_6.cpp
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

int StrStr(char s1[], char s2[]){
	int i=0;
	while(s1[i]){
		int j=0;
		while(s1[i+j] == s2[j]){
			if(s2[j+1] == 0)
				return i;
			j++;
		}
		i++;
	}
	return -1;
}


int main(){
	char a[64] = "JUAN ESTA CASADO CON MARIA";
	char b[64] = "ASADO";
	char c[64] = "ABCDE";
	char d[64] = "BCE";

	//cout << StrStr(a,b) << endl;
	//cout << StrStr(c,d) << endl;

    std::cout << StrStr(a,b) << std::endl;
    std::cout << StrStr(c,d) << std::endl;


	return 0;
}