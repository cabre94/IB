#include "misfuncs.h"

int main(){
	
	double arr[5];

	IngresaVector(arr,5);
	ImprimeVector(arr,5);
	OrdenaArrayNativo(arr,5);
	ImprimeVector(arr,5);

	vector<double> vec;
	vec.resize(3);

	IngresaVector(vec);
	ImprimeVector(vec);

	array<double, 3> std_arr;
	IngresaVector(std_arr);
	ImprimeVector(std_arr);
	
	return 0;
}

// Con amor, Cabre.