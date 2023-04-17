#include <iostream>
#include <array>
#include <vector>

using namespace std;

const int SIZE = 3;

// ---------------------------- arrays nativos ----------------------------- //
void ImprimeVector(double Vector[], int NumElementos){
	if(NumElementos <= 0)
		return;

	for(int i=0; i < NumElementos-1; i++)
		cout << Vector[i] << ' ';
	cout << Vector[NumElementos-1] << endl;
}

void IngresaVector(double Vector[], int NumElementos){
	cout << "Ingrese los elementos del array nativo de dimension " << NumElementos << " de a uno por vez.\n";
	for(int i=0; i < NumElementos; i++)
		cin >> Vector[i];
}

// ------------------------------ std::array ------------------------------- //
// Los std::array tienen una cantidad de tamaño fija. Esa informacion esta
// contenida dentro del array y se puede obtener con la funcion miembro size()
// asi que el segundo argumento lo podemos sacar.
// Por el momento, el tamaño del array tiene que ser conocido. Se puede hacer
// la funcion con un tamaño arbitrario, pero para eso hace falta ver templates
// que es un tema de mas adelante.
void IngresaVector_array(array<double, SIZE> arr){
	cout << "Ingrese los elementos del array de dimension " << arr.size() << " de a uno por vez.\n";
	for(size_t i=0; i < arr.size(); i++)
		cin >> arr[i];
}

void ImprimeVector_array(array<double, SIZE> arr){
	if(arr.size() <= 0)
		return;

	for(size_t i=0; i < arr.size()-1; i++)
		cout << arr[i] << ' ';
	cout << arr[arr.size()-1] << endl;
}

// ------------------------------ std::vector ------------------------------- //
// El std::vector tiene la ventaja sobre el std::array que puede tener tamaño
// variable
void IngresaVector_vector(vector<double> vec){
	cout << "Ingrese los elementos del vector de dimension " << vec.size() << " de a uno por vez.\n";
	for(size_t i=0; i < vec.size(); i++)
		cin >> vec[i];
}

void ImprimeVector_vector(vector<double> vec){
	if(vec.size() <= 0)
		return;

	for(size_t i=0; i < vec.size()-1; i++)
		cout << vec[i] << ' ';
	cout << vec[vec.size()-1] << endl;
}


int main(){

	double arr_nat[SIZE] = {0};
	array<double, SIZE> arr = {0};
	vector<double> vec(SIZE, 0);


	IngresaVector(arr_nat, SIZE);
	ImprimeVector(arr_nat, SIZE);

	IngresaVector_array(arr);
	ImprimeVector_array(arr);

	IngresaVector_vector(vec);
	ImprimeVector_vector(vec);

	return 0;
}

// Con amor, Cabre.