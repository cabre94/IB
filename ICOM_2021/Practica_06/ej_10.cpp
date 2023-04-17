#include <iostream>
#include <vector>

using namespace std;

/*
No se si lo comente en algun ejercicio antes, pero de ultima lo repito.
El size_t es un entero sin signo, lo suficientemente grande como para guardar
el tamaño de los contenedores de las librerias, por ejemplo, el std::vector o
el std::string.
Es decir, si vos tenes un std::vector vec y haces vec.size(), eso te devuelve
un size_t, no te devuelve un int. ¿Que pasa si usas un int en lugar de size_t
en un for por ejemplo? Problamente todo te anda, pero en teoria vec.size() te
retorna un numero que puede ser muy grande y no entrar en un int. En ese caso
vas a estar en problemas. Probablemente en la materia no te vaya a cambiar,
pero lo correcto es usar size_t.
Si no recuerdo mal, un size_t es un unsigned long, solo que con otro nombre
(un alias).
*/

struct StatWords {
public:
	struct StatRecord{
		string word;				// palabra en si
		unsigned int repCnt;		// cantidad de repeticiones
	};
	vector<StatRecord> records;

	// agrega una palabra: si ya está presente en records -> incrementa su repCnt
	// si no -> agrega un registro nuevo en records
	void addWord(const string &word);		
											
	void print();	// imprime las palabras y cuantas veces se repite
private:
	char lowercase(char c);			// Pasa a minucula un char
	// Busca si una palabra ya esta en la estadistica. Si esta, devuelve la
	// posicion, si no, devuelve un -1.
	int search(string word);
	// retorna string en minuscula y sacandole caracteresque no sean letras
	string lowerString(const string& word);
};

// Pasa a minucula un char
char StatWords::lowercase(char c){
	if(c>='A' && c<='Z')
		return c - 'A' + 'a';
	return c;
}

// retorna string en minuscula y sacandole caracteresque no sean letras
string StatWords::lowerString(const string& word){
	string res;

	for(size_t i=0; i < word.size(); ++i){
		if((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z'))
			res.push_back(lowercase(word[i]));
	}

	return res;
}

// Busca si una palabra ya esta en la estadistica. Si esta, devuelve la posicion, si no, devuelve un -1.
int StatWords::search(string word){
	int compara;

	for(size_t i=0; i < records.size(); i++){
		compara = word.compare(records[i].word);
		if(compara == 0)
			return i;
	}

	return -1;
}

// Agrega una palabra al statword
void StatWords::addWord(const string &word){
	string palabra = lowerString(word);

	int idx = search(palabra);

	if(idx == -1){
		StatRecord nueva;
		nueva.word = palabra;
		nueva.repCnt = 1;
		records.push_back(nueva);
	}else{
		records[idx].repCnt++;
	}
}

void StatWords::print(){
	cout << "Palabra\tRepeticiones" << endl;
	for(size_t i=0; i < records.size(); i++)
		cout << records[i].word << "\t" << records[i].repCnt << endl;
}


int main(){
	StatWords stats;
	string w;
	
	while (cin >> w)
		stats.addWord(w);

	stats.print();
	return 0;
}

// Con amor, Cabre.