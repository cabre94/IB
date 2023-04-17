#include "icom_helpers.h"

class Roedor{
public:
	Roedor(){
		cout << "Nace Roedor" << endl;
	}
	~Roedor(){
		cout << "Muere Roedor" << endl;
	}
	virtual void tipo(){
		cout << "Roedor" << endl;
	} 
};

class Raton: public Roedor{
public:
	Raton(){
		cout << "Nace Raton" << endl;
	}
	~Raton(){
		cout << "Muere Raton" << endl;
	}
	void tipo(){
		cout << "Raton" << endl;
	}
};

class Gerbo: public Roedor{
public:
	Gerbo(){
		cout << "Nace Gerbo" << endl;
	}
	~Gerbo(){
		cout << "Muere Gerbo" << endl;
	}
	void tipo(){
		cout << "Gerbo" << endl;
	}
};

class Hamster: public Roedor{
public:
	Hamster(){
		cout << "Nace Hamster" << endl;
	}
	~Hamster(){
		cout << "Muere Hamster" << endl;
	}
	void tipo(){
		cout << "Hamster" << endl;
	}
};

int main(){
	vector<Roedor *> roedores;
	roedores.resize(4);
	//Roedor* roedores[4];
	cout << endl;
	roedores[0] = new Roedor;
	cout << endl;
	roedores[1] = new Raton;
	cout << endl;
	roedores[2] = new Gerbo;
	cout << endl;
	roedores[3] = new Hamster;

	cout << endl << "Los tipos son:" << endl;
	roedores[0]->tipo();
	roedores[1]->tipo();
	roedores[2]->tipo();
	roedores[3]->tipo();

	cout << endl;
	delete roedores[0];
	delete roedores[1];
	delete roedores[2];
	delete roedores[3];

	cout << "No entiendo la diferencia" << endl;

	return 0;
}

// Con amor, Cabre.