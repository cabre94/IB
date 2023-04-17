#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <ctime>

/*
	- Chequear si le puedo agregar Color a la carta sin que explote todo (agregar constructor)
*/


using namespace std;

enum Palo{PICAS, TREBOL, CORAZONES, DIAMANTES, NUM_PALOS};

enum Color{ROJO, NEGRO};

enum Valor{AS = 1, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, OCHO, NUEVE, DIEZ, J, Q, K};


// Representaci�n de una carta a trav�s de un UDT "Carta"
struct Carta {
    // representacion
    Palo x;
    Valor z;
    
    // funcionalidad
    // imprime la carta (ej: "4 de PICAS") (TO DO)
    void imprimir();
    // retorna el color de una carta   (TO DO)
    Color getColor();
    // metoro para comparar cartas (usado en el ordenamiento)
    bool operator<(const Carta& otra) {
        return z < otra.z;
    }
};

// imprime la carta (ej: "4 de PICAS") (TO DO)
void Carta::imprimir(){
	// Printeamos el valor
	switch (z){
		case AS:
			cout << "AS de "; break;
		case J:
			cout << "J de "; break;
		case Q:
			cout << "Q de "; break;
		case K:
			cout << "K de "; break;
		default:
			cout << z << " de "; break;
	}
	// Ahora printeamos el palo
	switch (x){
		case PICAS:
			cout << "PICAS"; break;
		case TREBOL:
			cout << "TREBOL"; break;
		case CORAZONES:
			cout << "CORAZONES"; break;
		case DIAMANTES:
			cout << "DIAMANTES"; break;
		default:
			break;
	}
	cout << endl;
}

Color Carta::getColor(){
	if(x == PICAS || x == TREBOL)
		return NEGRO;
	else
		return ROJO;
};

// cantidad total de cartas
const unsigned int MAX_CARDS = K * NUM_PALOS;

// Representaci�n de un mazo de cartas a trav�s del UDT "Mazo"
struct Mazo {
    Carta vec[MAX_CARDS];          // vector nativo con todas las cartas
    unsigned int idxReparto = 0;   // indice de reparto, comienza en cero y se incrementa
                                   // de acuerdo a la repartida

    // construye un mazo: se completa vec y se resetea (se baraja y se inicializa idxReparto)
    Mazo() {
        fill();   
        reset();
    }

    // coloca todas las cartas en vec (TO DO)
    void fill();

    // funci�n que pide barajar (mezclar las cartas) e inicializa el indice de reparto
    void reset() {
        barajar();
        idxReparto = 0;
    }

    // mezcla todas las cartas (TODO)
    void barajar();

    // saca n cartas del mazo, las pone en cartas 
    // y ordena ese vector por n�mero
    void giveMeCards(vector<Carta>& cartas, unsigned int n) {
        assert(idxReparto + n < MAX_CARDS);
        for (unsigned int i = 0; i < n; ++i)
            cartas.push_back(vec[idxReparto++]);
        sort(cartas.begin(), cartas.end());
    }
};

// coloca todas las cartas en vec (TO DO)
void Mazo::fill(){
	for(int i = 0; i < NUM_PALOS; i++){
		for(int j = AS; j <= K; j++){
			vec[i*K + j-1] = {Palo(i), Valor(j)};
		}
	}
}

// mezcla todas las cartas (TODO)
void Mazo::barajar(){
	random_shuffle(vec, vec + MAX_CARDS);
}


// Representaci�n de un jugador a trav�s del UDT "Jugador"
struct Jugador {
    Jugador(const string& nombre_){
        nombre = nombre_;
    }

    string nombre;          // nombre del jugador
    vector<Carta> cartas;   // sus cartas

    // analiza que tipo de juego tiene
    // 2 cartas del mismo n�mero y las otras 3 de distinto n�mero
    bool esPar() {
        vector<int> reps = repeticiones();
        return reps[0] == 2 && reps[1] == 1;
    }

    // 2 x 2 cartas del mismo n�mero y la otra distinta
    bool esDoblePar() {
        vector<int> reps = repeticiones();
        return reps[0] == 2 && reps[1] == 2;
    }

    // 3 cartas del mismo n�mero y las otras 2 de distinto n�mero (TO DO)
    bool esPierna(){
		vector<int> reps = repeticiones();
        return reps[0] == 3 && reps[1] == 1;
	}

    // 3 cartas de un mismo n�mero y las otras  2 de otro n�mero (TO DO)
    bool esFull(){
		vector<int> reps = repeticiones();
        return reps[0] == 3 && reps[1] == 2;
	}

    // 4 cartas iguales de distinto palo (TO DO)
    bool esPoker(){
		vector<int> reps = repeticiones();
        return reps[0] == 4;
	}

    // las 5 cartas del mismo palo(ojo!) (TO DO)
    bool esColor(){
		vector<int> reps = repeticionesPalo();
        return reps[0] == 5;
	}

    // valores consecutivos (el AS puede aparecer al comienzo y al final) (TO DO)
    bool esEscalera(){
		Valor primera = cartas[0].z;
		if(cartas[1].z == Valor(primera+1) && cartas[4].z == Valor(primera+4))
			return true;
		else if(primera == AS && cartas[1].z == DIEZ && cartas[4].z == K){
			return true;
		}else
			return false;
	}

    // valores consecutivos del mismo palo (el AS puede aparecer al comienzo y al final) (TO DO)
    bool esEscaleraReal(){
		return esColor() && esEscalera();
	}

    // imprime el nombre del jugador y sus cartas
    void imprimir() {
        cout << nombre << endl;
        for (unsigned int i = 0; i < cartas.size(); i++)
            cartas[i].imprimir();
        cout << "===========" << endl;

    }

    // funci�n auxiliar para ayudar a definir el tipo de juego
    // cuenta cuantas cartas hay de cada valor y ordena esas repeticiones de mayor a menor
    // ejemplo (5 5 6 6 6) retorna (3, 2, 0, 0, ...)
    // ejemplo (5 5 6 6 9) retorna (2, 2, 1, 0, ...)
    // ejemplo (2 8 8 8 8) retorna (4, 1, 0, 0, ...)
    vector<int> repeticiones() {
        vector<int> v(K);
        for (unsigned int i = 0; i < cartas.size(); i++)
            v[cartas[i].z-1]++;
        sort(v.rbegin(), v.rend());
        return v;
    }

	vector<int> repeticionesPalo() {
        vector<int> v(NUM_PALOS);
        for (unsigned int i = 0; i < cartas.size(); i++)
            v[cartas[i].x]++;
        sort(v.rbegin(), v.rend());
        return v;
    }
};

// Representaci�n de un Crupier a trav�s del UDT "Crupier"
struct Crupier {
    // construye una instancia, recibe los participantes de la partida
    Crupier(vector<Jugador>& jugadores_) : jugadores(jugadores_) {}

    vector<Jugador>& jugadores;     // jugadores

    Mazo mazo;                      // mazo involucrado

    // resetea el mazo, baraja y reparte las cartas a los jugadores
    void inicioPartida() {
        mazo.reset();
        for (unsigned int i = 0; i < jugadores.size(); i++) {
            mazo.giveMeCards(jugadores[i].cartas, 5);            
        }
    }
};


// Funcion auxiliar para chequear cada mano
void check();
// main para probal un poco los m�todos.
int main(){
	/*
    vector<Jugador> gente = { Jugador("juan"), Jugador("pedro"), Jugador("maria"), Jugador("alicia")};
    Crupier cr(gente);
    srand(time(NULL));
    cr.inicioPartida();
    for (unsigned int i = 0; i < gente.size(); i++) {
        gente[i].imprimir();
        cout << " tiene poker: " << gente[i].esPoker() << endl;
        cout << " tiene full: " << gente[i].esFull() << endl;
        cout << " tiene par: " << gente[i].esPar() << endl;
        cout << " tiene doble par: " << gente[i].esDoblePar() << endl;
        cout << " tiene pierna: " << gente[i].esPierna() << endl;
        cout << " tiene color: " << gente[i].esColor() << endl;
        cout << " tiene escalera: " << gente[i].esEscalera() << endl;
        cout << " tiene escaleraReal: " << gente[i].esEscaleraReal() << endl;
    }*/
	check();
}



void check(){
	vector<Jugador> gente = {
		Jugador("Par"),
		Jugador("DoblePar"),
		Jugador("Pierna"),
		Jugador("Full"),
		Jugador("Poker"),
		Jugador("Color"),
		Jugador("Escalera"),
		Jugador("Escalera_con_AS"),
		Jugador("EscaleraReal")
	};

	// PAR
	gente[0].cartas.push_back(Carta {CORAZONES, J});
	gente[0].cartas.push_back(Carta {DIAMANTES, J});
	gente[0].cartas.push_back(Carta {PICAS, K});
	gente[0].cartas.push_back(Carta {CORAZONES, CUATRO});
	gente[0].cartas.push_back(Carta {TREBOL, TRES});
	sort(gente[0].cartas.begin(), gente[0].cartas.end());
	// Doble par
	gente[1].cartas.push_back(Carta {CORAZONES, J});
	gente[1].cartas.push_back(Carta {DIAMANTES, J});
	gente[1].cartas.push_back(Carta {PICAS, K});
	gente[1].cartas.push_back(Carta {CORAZONES, CUATRO});
	gente[1].cartas.push_back(Carta {TREBOL, CUATRO});
	sort(gente[1].cartas.begin(), gente[1].cartas.end());
	// pierna
	gente[2].cartas.push_back(Carta {CORAZONES, J});
	gente[2].cartas.push_back(Carta {DIAMANTES, J});
	gente[2].cartas.push_back(Carta {PICAS, J});
	gente[2].cartas.push_back(Carta {CORAZONES, CUATRO});
	gente[2].cartas.push_back(Carta {TREBOL, CINCO});
	sort(gente[2].cartas.begin(), gente[2].cartas.end());
	// full
	gente[3].cartas.push_back(Carta {CORAZONES, J});
	gente[3].cartas.push_back(Carta {DIAMANTES, J});
	gente[3].cartas.push_back(Carta {PICAS, J});
	gente[3].cartas.push_back(Carta {CORAZONES, CUATRO});
	gente[3].cartas.push_back(Carta {TREBOL, CUATRO});
	sort(gente[3].cartas.begin(), gente[3].cartas.end());
	// poker
	gente[4].cartas.push_back(Carta {CORAZONES, J});
	gente[4].cartas.push_back(Carta {DIAMANTES, J});
	gente[4].cartas.push_back(Carta {PICAS, J});
	gente[4].cartas.push_back(Carta {CORAZONES, J});
	gente[4].cartas.push_back(Carta {TREBOL, CUATRO});
	sort(gente[4].cartas.begin(), gente[4].cartas.end());
	// color
	gente[5].cartas.push_back(Carta {CORAZONES, J});
	gente[5].cartas.push_back(Carta {CORAZONES, Q});
	gente[5].cartas.push_back(Carta {CORAZONES, K});
	gente[5].cartas.push_back(Carta {CORAZONES, DIEZ});
	gente[5].cartas.push_back(Carta {CORAZONES, CUATRO});
	sort(gente[5].cartas.begin(), gente[5].cartas.end());
	// escalera
	gente[6].cartas.push_back(Carta {CORAZONES, CINCO});
	gente[6].cartas.push_back(Carta {DIAMANTES, CUATRO});
	gente[6].cartas.push_back(Carta {PICAS, SEIS});
	gente[6].cartas.push_back(Carta {CORAZONES, OCHO});
	gente[6].cartas.push_back(Carta {TREBOL, SIETE});
	sort(gente[6].cartas.begin(), gente[6].cartas.end());
	// escalera con as
	gente[7].cartas.push_back(Carta {CORAZONES, J});
	gente[7].cartas.push_back(Carta {DIAMANTES, Q});
	gente[7].cartas.push_back(Carta {PICAS, K});
	gente[7].cartas.push_back(Carta {CORAZONES, AS});
	gente[7].cartas.push_back(Carta {TREBOL, DIEZ});
	sort(gente[7].cartas.begin(), gente[7].cartas.end());
	// escalera real
	gente[8].cartas.push_back(Carta {DIAMANTES, Q});
	gente[8].cartas.push_back(Carta {DIAMANTES, J});
	gente[8].cartas.push_back(Carta {DIAMANTES, K});
	gente[8].cartas.push_back(Carta {DIAMANTES, AS});
	gente[8].cartas.push_back(Carta {DIAMANTES, DIEZ});
	sort(gente[8].cartas.begin(), gente[8].cartas.end());


	for (unsigned int i = 0; i < gente.size(); i++) {
        gente[i].imprimir();
        cout << " tiene poker: " << gente[i].esPoker() << endl;
        cout << " tiene full: " << gente[i].esFull() << endl;
        cout << " tiene par: " << gente[i].esPar() << endl;
        cout << " tiene doble par: " << gente[i].esDoblePar() << endl;
        cout << " tiene pierna: " << gente[i].esPierna() << endl;
        cout << " tiene color: " << gente[i].esColor() << endl;
        cout << " tiene escalera: " << gente[i].esEscalera() << endl;
        cout << " tiene escaleraReal: " << gente[i].esEscaleraReal() << endl;
    }
}