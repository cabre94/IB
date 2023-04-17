/*
date: 20-10-21
File: 03_evitando_el_megabochazo.cpp
Author : Facundo Martin Cabrera
Email: cabre94@hotmail.com facundo.cabrera@ib.edu.ar
GitHub: https://github.com/cabre94
GitLab: https://gitlab.com/cabre94
Description: 
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int dias = 4;

/*
Viendo los .txt uno ve que si guardas las probabilidades en un vector, el indice
es la cantidad de dias dedicado. Pero me gusta mas no asumir eso a pesar de los
txt que nos dan, y guardar los dias en una estructura junto a la probabilidad
*/

struct diaProb{
	int d;
	float p;
};

void minimiza(const vector<diaProb>& A, const vector<diaProb>& B, const vector<diaProb>& C){
	int res[3] = {0};
	double min_p = A[0].p * B[0].p * C[0].p;
	double prod;

	for(int i=0; i <= dias; ++i){
		for(int j=0; j <= (dias-A[i].d); ++j){
			for(int k=0; k <= (dias-A[i].d-B[j].d); ++k){
				// Probabilidad de desaprobar
				prod = A[i].p * B[j].p * C[k].p;

				// Si la probabilidad es menor que la actual minima,
				// actualizamos el estado
				if(prod < min_p){
					min_p = prod;
					res[0] = A[i].d;
					res[1] = B[j].d;
					res[2] = C[k].d;
				}
			}
		}
	}

	cout << "Materia A: " << res[0] << " dias" << endl;
	cout << "Materia B: " << res[1] << " dias" << endl;
	cout << "Materia C: " << res[2] << " dias" << endl;
}



int main(){

	vector<diaProb> A, B, C;

	int dia;
	float prob;

	ifstream file("A.txt");
	if(file.is_open()){
		while (file >> dia >> prob)
			A.push_back({dia, prob});
        file.close();
    }else{
		throw string("No se pudo abrir A.txt");
	}

	file.open("B.txt");
	if(file.is_open()){
		while (file >> dia >> prob)
			B.push_back({dia, prob});
        file.close();
    }else{
		throw string("No se pudo abrir B.txt");
	}

	file.open("C.txt");
	if(file.is_open()){
		while (file >> dia >> prob)
			C.push_back({dia, prob});
        file.close();
    }else{
		throw string("No se pudo abrir C.txt");
	}

	minimiza(A, B, C);

	return 0;
}