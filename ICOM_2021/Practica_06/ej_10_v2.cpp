#include <iostream>
#include <vector>

using namespace std;

struct StatWords {
public:
	struct StatRecord{
		string word;				// palabra en si
		unsigned int repCnt;		// cantidad de repeticiones
	};
	vector<StatRecord> records;

	void addWord(const string &word);		// agrega una palabra: si ya está presente en records -> incrementa su repCnt
											// si no -> agrega un registro nuevo en records
	void print();					        // imprime las palabras y cuantas veces se repite
private:
	char lowercase(char c);			// Pasa a minucula un char
	char uppercase(char c);			// Pasa a mayuscula un char
	// Busca si una palabra ya esta en la estadistica. Si esta, devuelve la posicion, si no, devuelve un -1.
	int search(string word);
	// Filtra cada string, poniendo la primera letra en mayuscula, el resto en minuscula y sacandole cualquier caracter caca que no sea una letra
	string standardizeString(string word);
};

// Pasa a minucula un char
char StatWords::lowercase(char c){
	if(c>='A' && c<='Z')
		return c - 'A' + 'a';
	return c;
}

// Pasa a mayuscula un char
char StatWords::uppercase(char c){
	if('a'<=c && c<='z')
		return c - 'a' + 'A';
	return c;
}

// Filtra cada string, poniendo la primera letra en mayuscula, el resto en minuscula y sacandole cualquier caracter caca que no sea una letra
string StatWords::standardizeString(string word){
	bool mayus = true;
	string res;

	for(size_t i=0; i < word.size(); ++i){
		if( (word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z') ){
			if(mayus){
				res.push_back(uppercase(word[i]));
				mayus = false;
			}else{
				res.push_back(lowercase(word[i]));
			}
		}
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
	string palabra = standardizeString(word);
	// string palabra = word;

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
	for(int i=0; i < records.size(); i++)
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