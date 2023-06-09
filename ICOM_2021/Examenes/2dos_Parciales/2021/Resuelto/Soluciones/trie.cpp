#include <cassert>
#include <cctype>
#include <string.h>
#include <fstream>
#include <iostream>
#include <list>

using namespace std;

#define ALPHABET_SIZE 26
// funci�n auxiliar: retorna el indice que le corresponde a un caracter dado
static int getIndexForChar(int c)
{
	int ret = toupper(c) - 'A';     //  calcula el indice pasando la letra a may�scula
	assert(ret >= 0 && ret < ALPHABET_SIZE);
	return ret;
}

// funci�n auxiliar: retorna el caracter que le corresponde a un indice dado
static char getCharForIndex(int i)
{
	assert(i >= 0 && i < ALPHABET_SIZE);
	return i + 'A';
}

// Nodo de un Trie
struct TrieNode {
	TrieNode() {
		for (int i = 0; i < ALPHABET_SIZE; ++i)
			children[i] = nullptr;
	}

	~TrieNode() {
		for (int i = 0; i < ALPHABET_SIZE; ++i)
			delete children[i];
	}

	int numKeys() {
		if (this == nullptr)
			return 0;
		int ret = 0;
		if (defineKey)
			ret = 1;
		for (int i = 0; i < ALPHABET_SIZE; i++)
			ret += children[i]->numKeys();
		return ret;
	}

	bool defineKey = false;    		                 // true/false si define o no una clave
	TrieNode *children[ALPHABET_SIZE];       // puntero a los hijos de este prefix, 
											 // nullptr si no hay hijo que expanda en esa letra
};

// estructura de un Trie
struct Trie {
	Trie() {
		root = new TrieNode;
	}
	~Trie() {
		delete root;
	}

	// agrega una clave al Trie
	void insertKey(const char key[]) {
		TrieNode* pCursor = root;
		// va recorriendo el prefix, creando nodos si es necesario
		for (size_t level = 0; level < strlen(key); level++) {
			int index = getIndexForChar(key[level]);
			if( pCursor->children[index] == nullptr )
				pCursor->children[index] = new TrieNode;
			pCursor = pCursor->children[index];
		}
		// marca defineKey en el �ltimo valor de pCursor si es que no estaba ya definido como clave
		if (pCursor->defineKey == false) {
			pCursor->defineKey = true;
			numKeys++;   // aumento la cantidad de claves del trie
		}
	}
	
	// busca el nodo donde termina un prefix
	TrieNode* searchPrefix(const char key[]) const {
		int length = strlen(key);
		TrieNode* pCursor = root;

		// va recorriendo el prefix
		for (int level = 0; level < length; level++) {
			int index = getIndexForChar(key[level]);
			if (!pCursor->children[index])  // si no se extiende, la clave no existe
				return nullptr;
			pCursor = pCursor->children[index];
		}
		return pCursor;
	}

	bool existKey(const char key[]) {
		int length = strlen(key);
		int index;
		TrieNode* pCursor = searchPrefix(key);
		return pCursor != nullptr && pCursor->defineKey == true;
	}
	int trieNumWordsWithPrefix(const char* prefix) {
		TrieNode* keyNode = searchPrefix(prefix);
		return keyNode->numKeys();
	}

	bool check() {
		int nk = root->numKeys();
		return nk == numKeys;
	}

	TrieNode *root;		    // contenedor real de datos
	unsigned int numKeys = 0;	// n�mero de claves en el trie
};

// TODO
void trieGetEnabledKeys(const Trie* trie, const char* prefix, bool enabledKeys[ALPHABET_SIZE])
{
	for (int i = 0; i < ALPHABET_SIZE; ++i)
		enabledKeys[i] = false;
	TrieNode* tn = trie->searchPrefix(prefix);
	if (tn) {
		for (int i = 0; i < ALPHABET_SIZE; ++i)
			if(tn->children[i] != nullptr)
				enabledKeys[i] = true;
	}

}

// TODO
using ListWord = list<string>;

void collectKeys(TrieNode* tn, const string& prefix, ListWord& l)
{
	if (tn->defineKey)
		l.push_back(prefix);
	for (int i = 0; i < ALPHABET_SIZE; ++i)
		if (tn->children[i] != nullptr)
			collectKeys(tn->children[i], prefix + getCharForIndex(i), l);

}

ListWord trieGetKeys(const Trie* trie, const char* prefix)
{
	ListWord l;
	TrieNode* tn = trie->searchPrefix(prefix);
	if (tn) {
		collectKeys(tn, prefix, l);
	}
	return l;
}

int main()
{
	Trie* pTrie = new Trie;

	ifstream ifile("calles.txt");
	assert(ifile.is_open());
	string s;

	while (ifile >> s) {
		pTrie->insertKey(s.c_str());
	}

	cout << "Chequeo: " << pTrie->check() << endl;

	bool enabledKeys[ALPHABET_SIZE];
	trieGetEnabledKeys(pTrie, "A", enabledKeys);
	for (auto b : enabledKeys)
		cout << b << " ";
	cout << endl;

	ListWord list = trieGetKeys(pTrie, "M");
	cout << "claves con M =====>\n";
	for (auto& l : list)
		cout << l << endl;

	list = trieGetKeys(pTrie, "MO");
	cout << "claves con MO =====>\n";
	for (auto& l : list)
		cout << l << endl;

	list = trieGetKeys(pTrie, "MOR");
	cout << "claves con MOR =====>\n";
	for (auto& l : list)
		cout << l << endl;


	delete pTrie;

	return 0;
}

