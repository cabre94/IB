#include <iostream>
#include <array>
#include <cmath>

using namespace std;

/*
Algunas cosas del ejercicio que a mi entender no quedan claras:
- Nunca te dan un dt, asi que asumo que es 1
- Si llega a la pared no se dice nada de que hacer, si rebota, aparece del otro lado etc.
- Es mas, ni siquiera se si hay pared o estan en el oceano.
*/

struct V2_t{
	double x, y;
	V2_t operator+(V2_t v){return V2_t{x + v.x, y + v.y};}
	V2_t operator-(V2_t v){return V2_t{x - v.x, y - v.y};}
	double norm(){return sqrt(x*x + y*y);}
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

// Inicializa todos los peces con posiciones al azar dentro de un área
// cuadrada de n x n y con velocidades al azar con 0 < |v| < maxVel.
void Cardumen::initialize(int n, double maxVel_, double maxDist_){
	maxDist = maxDist_;
	maxVel = maxVel_;

	for(int i=0; i < MAX_PECES; i++){
		// Inicializamos las posiciones dentro de una area de nxn
		peces[i].pos.x = (double) rand() / (RAND_MAX / n);
		peces[i].pos.y = (double) rand() / (RAND_MAX / n);

		// Inicializamos las componentes de velocidades entre -Vmax y Vmax
		peces[i].vel.x = (double) rand() / (RAND_MAX / (2.0*maxVel)) - maxVel; // -Vmax < Vx < Vmax
		peces[i].vel.y = (double) rand() / (RAND_MAX / (2.0*maxVel)) - maxVel;

		// Limitamos la velocidad
		double norm = peces[i].vel.norm();
		if(norm > maxVel){
			peces[i].vel.x = peces[i].vel.x * (maxVel / norm);
			peces[i].vel.y = peces[i].vel.y * (maxVel / norm);
		}
	}
}

// Calcula y retorna el centro de masa de los peces(para su uso en R1)
V2_t Cardumen::calculateCM(){
	V2_t cm = {0, 0};

	for(int i=0; i < MAX_PECES; i++){
		cm = cm + peces[i].pos;
	}

	cm.x /= MAX_PECES;
	cm.y /= MAX_PECES;

	return cm;
}

// Calcula y retorna la veloidad media de todos peces(para su uso en R3)
V2_t Cardumen::calculateVM(){
	V2_t vm = {0, 0};

	for(int i=0; i < MAX_PECES; i++){
		vm = vm + peces[i].vel;
	}

	vm.x /= MAX_PECES;
	vm.y /= MAX_PECES;

	return vm;
}

// aplica la regla 1 al pez i retornando su deltaV por R1
V2_t Cardumen::applyR1(int i, V2_t cm){
	V2_t dv1 = (cm - peces[i].pos);
	dv1.x = dv1.x / 8;
	dv1.y = dv1.y / 8;

	// peces[i].vel = peces[i].vel - dv1;
	return dv1;
}

// aplica la regla 2 al pez i retornando su deltaV por R2
V2_t Cardumen::applyR2(int i){
	V2_t dv2 = {0, 0};

	for(int j = 0; j < MAX_PECES; j++){
		if(j != i){		// Si no es el mismo pez
			V2_t dr = (peces[j].pos - peces[i].pos);
			double norm = dr.norm();
			if(norm < maxDist){		//	Si estan a dist menor que maxDist
				dr.x = dr.x / norm;
				dr.y = dr.y / norm;
				dv2 = dv2 + dr;
			}
		}
	}

	return dv2;
}

// aplica la regla 3 al pez i retornando su deltaV por R3
V2_t Cardumen::applyR3(int i, V2_t vm){
	V2_t dv3 = (vm - peces[i].vel);
	dv3.x = dv3.x / 8;
	dv3.y = dv3.y / 8;

	// peces[i].vel = peces[i].vel - dv1;
	return dv3;
}

// hace evolucionar el cardumen 1 paso de tiempo. Calcula CM, VM y las
// nuevas velocidades de todos los peces a partir de las aplicaciones
// de las reglas 1, 2 y 3 aplicando además el limitador de velocidad.
// Actualiza las velocidades y posiciones de todos los peces del cardumen.
void Cardumen::doStep(){
	V2_t cm = calculateCM();
	V2_t vm = calculateVM();

	for(int i=0; i < MAX_PECES; i++){
		V2_t dv1 = applyR1(i, cm);
		V2_t dv2 = applyR2(i);
		V2_t dv3 = applyR3(i, vm);

		// Actualizamos posicion y velocidad
		V2_t dv = dv1 + dv2 + dv3;
		peces[i].vel = peces[i].vel + dv;
		peces[i].pos = peces[i].pos + peces[i].vel;

		// Limitamos la velocidad
		double norm = peces[i].vel.norm();
		if(norm > maxVel){
			peces[i].vel.x = peces[i].vel.x * (maxVel / norm);
			peces[i].vel.y = peces[i].vel.y * (maxVel / norm);
		}
	}

}
/*
Para hacerla facil actualizamos el pez 1. Despues
el pez 2 PERO con los valores del pez 1 ya actualizados etc etc y el ultimo pez se actualiza con
la info del resto de los peces ya actualizados.
Si quisieramos que todos los peces se actualicen con la info del resto en un dt anterior, tendriamos
que ir guardando los dv y dr de cada pez en un vector y cuando tenemos todos, recien ahi actualizarlos.
En este momento me da paja hacerlo asi, ya subire un version mas completa.
*/


// Imprime el estado actual de cardumen. (Posiciones y velocidades)
void Cardumen::print(){
	for(int i=0; i < MAX_PECES; i++){
		cout << "Pez " << i+1 << "\tpos: (" << peces[i].pos.x << ", " << peces[i].pos.y << ")";
		cout << " - vel: (" << peces[i].vel.x << ", " << peces[i].vel.y << ")" << "\t|V|: " << peces[i].vel.norm() << endl;
	}
}