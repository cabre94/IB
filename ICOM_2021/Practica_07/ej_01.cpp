#include <iostream>
#include <string>

using namespace std;

// Pasa a minucula un char
char lowercase(char c){
	if(c>='A' && c<='Z')
		return c - 'A' + 'a';
	return c;
}

// Pasa a mayuscula un char
char uppercase(char c){
	if(c>='a' && c<='z')
		return c - 'a' + 'A';
	return c;
}

void CapitalizeFirst(std::string &phrase){
	bool newWord = true;

	for(size_t i=0; i<phrase.size(); ++i){
		if(phrase[i] == ' ' || phrase[i] == '('){
			newWord = true;
		}else if(newWord){
			phrase[i] = uppercase(phrase[i]);
			newWord = false;
		}else{
			phrase[i] = lowercase(phrase[i]);
		}
	}
}

int main(){

	string str = "este es el primer parcial de introduccion al computo";

	// string str;
	// getline(cin, str);

	CapitalizeFirst(str);

	cout << str << endl;

	return 0;
}

// Con amor, Cabre.