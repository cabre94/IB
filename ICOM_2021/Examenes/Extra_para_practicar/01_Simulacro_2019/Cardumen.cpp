#include <iostream>
#include <array>

using namespace std;

struct V2_t{
	double x, y;
};

struct Pez_t{
	V2_t pos;
	V2_t vel;
};

struct Cardumen{
	double maxVel;
	double maxDist;

	static const int MAX_PECES = 16;
	std::array<Pez_t, MAX_PECES> peces;

	// Inicializa todos los peces con posiciones al azar dentro de un área
	// cuadrada de n x n y con velocidades al azar con 0 < |v| < maxVel.
	void initialize(int n, double maxVel_, double maxDist_);
	// Calcula y retorna el centro de masa de los peces(para su uso en R1)
	V2_t calculateCM();
	// Calcula y retorna la veloidad media de todos peces(para su uso en R3)
	V2_t calculateVM();
	// aplica la regla 1 al pez i retornando su deltaV por R1
	V2_t applyR1(int i, V2_t cm);
	// aplica la regla 2 al pez i retornando su deltaV por R2
	V2_t applyR2(int i);
	// aplica la regla 3 al pez i retornando su deltaV por R3
	V2_t applyR3(int I, V2_t vm);
	// hace evolucionar el cardumen 1 paso de tiempo. Calcula CM, VM y las
	// nuevas velocidades de todos los peces a partir de las aplicaciones
	// de las reglas 1, 2 y 3 aplicando además el limitador de velocidad.
	// Actualiza las velocidades y posiciones de todos los peces del cardumen.
	void doStep();
	// Imprime el estado actual de cardumen. (Posiciones y velocidades)
	void print();
};

int main(){
	const int NUM_PASOS = 100;
	Cardumen c;
	
	c.initialize(40, 4, 3);
	for (int i = 0; i < NUM_PASOS; ++i) {
		c.doStep();
		c.print();
	}
	
	return 0;
}
