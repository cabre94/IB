#include <iostream>

using namespace std;

// Función StrStr que reciba dos strings nativos y busque sobre el primero de
// ellos por la ocurrencia del segundo. tiene que devolver la ṕosicion de s1
// donde aparece s2, si no aparece hay que devoler un -1.
// Necesitamos dos while, uno para ir ubicandonos en los caracteres del primer
// string y otro para ir recorriendo ambos caracteres simultaneamente.
int StrStr(char s1[], char s2[]){
	int i=0;
	
	while(s1[i]){	// Mientras no lleguemos al final del primer string
		int j=0;
		while(s1[i+j] == s2[j]){	// Si coindiden los caracteres
			// Si llegamos al final del segundo, entonces esta adentro del primero
			if(s2[j+1] == 0)
				return i;
			j++;
		}
		i++;
	}

	return -1;
}

int main(){
	char a[64] = "JUAN ESTA CASADO CON MARIA";
	char b[64] = "ASADO";
	char c[64] = "ABCDE";
	char d[64] = "BCE";

	cout << StrStr(a,b) << endl;
	cout << StrStr(c,d) << endl;

	return 0;
}

// Con amor, Cabre.