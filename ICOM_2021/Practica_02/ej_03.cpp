#include <iostream>
#include <cmath>

using namespace std;

// Esta version sigue agregando terminos de la sumatoria hasta que dicho valor
// sea tan pedorro (o sea, tan chico) que no cambie el valor de la variable
// donde estamos guardando la sumatoria. Es por esto que hacerlo con double
// hace que tarde un siglo en correr.
float Leibniz(){
	int i = 0;
	float sum = 0, previo = 3; // Se puede hacer con double pero tarda un siglo

	while(sum != previo){
		previo = sum;
		if(i % 2 == 0){
			sum += 4.0/(2*i+1);
		}else{
			sum -= 4.0/(2*i+1);
		}
		i++;
	}
	return sum;
}

// En esta version le damos un epsilon para cortar la sumatoria cuando los
// terminos que agregamos sean menores que ese epsilon
double Leibniz_v2(double epsi){
	int i = 0;
	double sum = 0, previo = 3;

	while(abs(sum - previo) > epsi){
		previo = sum;
		if(i % 2 == 0){
			sum += 4.0/(2*i+1);
		}else{
			sum -= 4.0/(2*i+1);
		}
		i++;
	}
	return sum;
}

int main(){

	// cout.precision(9); // Esto cambia la cantidad de digitos que printea el programa.
	cout << "π = " << Leibniz() << endl;
	cout << "π = " << Leibniz_v2(0.000001) << endl;

	return 0;
}

// Con amor, Cabre.