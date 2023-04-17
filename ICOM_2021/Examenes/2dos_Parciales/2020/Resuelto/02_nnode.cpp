#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

class NNode{
	public:
		// inicializa un nuevo nodo con 'v' como valor del nodo
		NNode(int v);
		// destruye el nodo
		~NNode();
		// agrega un nuevo nodo con valor 'v' cumpliendo los requerimientos dados
		void addNode(int v);  // ToDo
		// cuenta y retorna la cantidad de nodos, incluyendose a si mismo
		int peso();
		// retorna true/false indicando si 'v' esta contenido como 'value' en algun nodo
		bool esMiembro(int v);
		// retorna true si es un nodo terminal (sin hijos), falso en caso contrario
		bool esHoja();
		// retorna la altura (cantidad de niveles) que tiene el arbol.
		int altura();
	
	private:
		int value;
		static const int MAX_CHILD = 4;
		NNode *children[MAX_CHILD];
};


int main(){
	srand((unsigned int) time(NULL));
	NNode* arbol = new NNode(rand() % 1000);

	int hprev = 1;
	int pprev = 1;

	for (int i = 2; i <= 2500; i++) {
		arbol->addNode(rand() % 1000);
		int h = arbol->altura();
		if (h != hprev) {
			assert(i == arbol->peso());
			cout << "n: " << i - 1 << ", w: " << i - 1 << ", h: " << hprev << endl;
			cout << "n: " << i << ", w: " << arbol->peso() << ", h: " << h << ", n_lev: " << i - pprev << "\n...\n";
			hprev = h;
			pprev = i;
		}
	}

	cout << "Peso:        " << arbol->peso() << endl;
	cout << "Altura:      " << arbol->altura() << endl;
	cout << "esta el 10?: " << arbol->esMiembro(10) << endl;
	cout << "esta el 20?: " << arbol->esMiembro(20) << endl;
	cout << "esta el 30?: " << arbol->esMiembro(30) << endl;
	cout << "esta el 40?: " << arbol->esMiembro(40) << endl;
	cout << "esta el 50?: " << arbol->esMiembro(50) << endl;

	delete arbol;

	return 0;
}

// -------------------------------------------------------------------------- //
NNode::NNode(int v) : value(v) {
	for(int i=0; i < MAX_CHILD; i++)
		children[i] = nullptr;
}

NNode::~NNode(){
	for(int i=0; i < MAX_CHILD; i++)
		delete children[i];
}

void NNode::addNode(int v){
	// No me gusto como me quedo, capaz se pueda hacer mejor
	for(int i=0; i < MAX_CHILD; i++){
		if(children[i] == nullptr){
			children[i] = new NNode(v);
			return;
		}
	}

	int weight = children[0]->peso();

	for(int i=1; i < MAX_CHILD; i++){
		if(weight != children[i]->peso()){
			children[i]->addNode(v);
			return;
		}
	}

	children[0]->addNode(v);
	return;
}

int NNode::peso(){
	if(this == nullptr)
		return 0;
	
	int res = 1;
	for(int i=0; i < MAX_CHILD; i++)
		res += children[i]->peso();
	
	return res;
}

bool NNode::esMiembro(int v){
	if(this == nullptr)
		return false;
	if(value == v)
		return true;
	
	for(int i=0; i < MAX_CHILD; i++){
		if(children[i]->esMiembro(v))
			return true;
	}
	
	return false;
}

bool NNode::esHoja(){
	for(int i=0; i < MAX_CHILD; i++){
		if(children[i] != nullptr)
			return false;
	}
	return true;
}

int NNode::altura(){
	if(this == nullptr)
		return 0;
	return 1 + children[0]->altura();
}