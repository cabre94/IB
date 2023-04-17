/*
date: 27-10-21
File: 02_Trie.cpp
Author : Facundo Martin Cabrera
Email: cabre94@hotmail.com facundo.cabrera@ib.edu.ar
GitHub: https://github.com/cabre94
GitLab: https://gitlab.com/cabre94
Description:
*/

#include <iostream>

#define ALPHABET_SIZE 26

using namespace std;

struct Trie_node{
	Trie_node() : defineKey(false) {
		defineKey = false;
		// Trie_node() : defineKey(false), children{{nullptr}} {
		for(int i=0; i < ALPHABET_SIZE; i++)
			children[i] = nullptr;
	}
	~Trie_node(){
		for(int i=0; i < ALPHABET_SIZE; i++)
			delete children[i];
	}

	int insertKey(const char *key);
	bool existKey(const char *key);
	int numberOfKeys();
	int numWordsWithPrefix(const char *prefix);

	bool defineKey;	// true/false si define o no una clave
	Trie_node* children[ALPHABET_SIZE];
};



struct Trie{
	Trie() : root(new Trie_node), numKeys(0) {}
	~Trie(){delete root;}
	// inserta una nueva clave si no está presente o lo marca con defineKey
	// si ya existía como prefix de otras claves
	void insertKey(const char *key){numKeys += root->insertKey(key);}
	// retorna verdadero/falso indicando si la clave existe.
	bool existKey(const char *key){return root->existKey(key);}
	// Chequea la consistencia entre la cantidad de nodos que dice el trie y
	// la cantidad de nodos que definen key.
	// Retorna un bool indicando si hay o nó consistencia.
	bool check(){return numKeys == root->numberOfKeys();}
	// Retorna la cantidad de claves que tienen un prefix determinado.
	int numWordsWithPrefix(const char *prefix){return root->numWordsWithPrefix(prefix);}

	Trie_node *root;			// contenedor real de datos
	unsigned int numKeys;		// número de claves en el trie
};


int main(){

	Trie trie;

	trie.insertKey("telleski");
	trie.insertKey("casado");
	trie.insertKey("casa");
	trie.insertKey("casamiento");
	trie.insertKey("vdsgrsgsrrgrgs");

	if(trie.existKey("telleski"))
		cout << "telleski esta en el Trie" << endl;
	else
		cout << "telleski esta en el Trie" << endl;
	
	if(trie.existKey("kk"))
		cout << "kk esta en el Trie" << endl;
	else
		cout << "kk no esta en el Trie" << endl;


	// if(trie.check())
	// 	cout << "El TrieCheck da bien" << endl;
	// else
	// 	printf("El trieCheck da como el orto\n");
	
	cout << "Hay " << trie.numWordsWithPrefix("cas") << " claves con el prefijo cas" << endl;
	cout << "Hay " << trie.numWordsWithPrefix("ca") << " claves con el prefijo ca" << endl;
	cout << "Hay " << trie.numWordsWithPrefix("casam") << " claves con el prefijo casam" << endl;


	return 0;
}




int Trie_node::insertKey(const char *key){
	if(*key){	// Si todavia quedan letras en key
		int idx_letter = *key - 'a';
		if(children[idx_letter] == nullptr)
			children[idx_letter] = new Trie_node();
		return children[idx_letter]->insertKey(key + 1);
	}else{		// Si es el 0 indicando que termino la palabra
		if(defineKey)	// Si es una palabra ya definida, terminamos
			return 0;
		else{
			// Si no esta definida, retornamos 1 para el contador
			defineKey = true;
			return 1;
		}
	}
}

bool Trie_node::existKey(const char *key){
	if(*key == 0)
		return defineKey;
	if(children[*key - 'a'] == nullptr)
		return false;
	return children[*key - 'a']->existKey(key+1);
}

int Trie_node::numberOfKeys(){
	int res = 0;
	if(this == nullptr)
		return res;
	if(defineKey)
		res += 1;
	for(int i=0; i < ALPHABET_SIZE; i++)
		res += children[i]->numberOfKeys();
	return res;
}

int Trie_node::numWordsWithPrefix(const char *prefix){
	if(*prefix == 0)
		return numberOfKeys();
	if(children[*prefix - 'a'] == nullptr)
		return 0;
	return children[*prefix - 'a']->numWordsWithPrefix(prefix + 1);

}