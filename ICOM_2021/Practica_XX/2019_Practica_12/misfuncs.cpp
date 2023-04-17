#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;


// ============================================================= //
// FUNCIONES QUE IMPRIMEN E INGRESAN VALORES A UN VECTOR O ARRAY //
// ============================================================= //

// Para ARREGLOS NATIVOS
// Imprime un arreglo nativo de doubles
void ImprimeVector(double Vector[], int NumElementos){
	if( NumElementos <= 0) return;
	for(int i=0; i < NumElementos-1; i++)
		cout << Vector[i] << ' ';
	cout << Vector[NumElementos-1] << endl;
}

// Imprime un arreglo nativo de enteros
void ImprimeVector(int Vector[], int NumElementos){
	if( NumElementos <= 0) return;
	for(int i=0; i < NumElementos-1; i++)
		cout << Vector[i] << ' ';
	cout << Vector[NumElementos-1] << endl;
}

void IngresaVector(double Vector[], int NumElementos){
	cout << "Ingrese los elementos del vector de dimension " << NumElementos << " de a uno por vez.\n";
	for(int i=0; i < NumElementos; i++)
		cin >> Vector[i];
}


// Para ARRAYS con la libreria <array>
template<size_t N>
void ImprimeVector(array<double, N> &Array, int NumElementos){
	if( NumElementos <= 0) return;
	for(int i=0; i < NumElementos-1; i++)
		cout << Array[i] << ' ';
	cout << Array[NumElementos-1] << endl;
}

template<size_t N>
void IngresaVector(array<double, N> &Array, int NumElementos){
	cout << "Ingrese los elementos del vector de dimension " << NumElementos << " de a uno por vez.\n";
	for(int i=0; i < NumElementos; i++)
		cin >> Array[i];
}
// El problema usando la libreria <array> es que en el argumento de la funcion, hay que decirle el tamaño de la variable Array. 
// Pero uno en general lo quiere hacer en general. Googleando encontre que en general dan dos alternativas: la primera es usar la
// libreria vector, que no es lo que querriamos aca. La segunda es usar ese comandito -template<size_t N>-. El tema es que no tengo ni
// idea de que es, ni como funciona. Tampoco se porque, pero hay que ponerlo antes de cada declaracion e implementacion de una funcion 
// que lo tenga, por eso esta cuatro veces. Cuestion que esto asi como esrta parece funcionar.

// Para VECTORES
// Es importante a la funcion pasarle la referencia del vector (o sea, ponerle el &). Si no, a la funcion se le va a mandar una copia
// del vector, y no va a modificar el original. Esto para la funcion ImprimeVector en realidad no importa mucho, ya que imprimir en pantalla
// la copia o el original da igual. Pero si lo queremos modificar ahi si es importante. Lo mas paja es que la forma de pasar el argumento como
// referencia es distinto para los arrays nativos que para los implementados con <array> y <vector>.
void ImprimeVector(vector<double> &Vector, int NumElementos){
	if( NumElementos <= 0) return;
	for(int i=0; i < NumElementos-1; i++)
		cout << Vector[i] << ' ';
	cout << Vector[NumElementos-1] << endl;
}

//void IngresaVector(vector<double> Vector, int NumElementos){
void IngresaVector(vector<double> &Vector, int NumElementos){
	cout << "Ingrese los elementos del vector de dimension " << NumElementos << " de a uno por vez.\n";
	for(int i=0; i < NumElementos; i++)
		cin >> Vector[i];
}


// ============================================================= //
//                   FUNCIONES DE ORDENAMIENTO                   //
// ============================================================= //

// Ordena array nativo de enteros en forma creciente
void OrdenaArrayNativo(int V[], int n){
	int aux;
	for(int i=n-1; i>0; i--){
		for(int j=0; j < i; j++){
			if(V[j] > V[j+1]){
				aux = V[j];
				V[j] = V[j+1];
				V[j+1] = aux; 
			}
		}
	}
	return;
}

// Ordena array nativo de doubles en forma creciente
void OrdenaArrayNativo(double V[], int n){
	double aux;
	for(int i=n-1; i>0; i--){
		for(int j=0; j < i; j++){
			if(V[j] > V[j+1]){
				aux = V[j];
				V[j] = V[j+1];
				V[j+1] = aux; 
			}
		}
	}
	return;
}

// Invierte los elementos de un array nativo de enteros
void InvierteArrayNativo(int V[], int n){
	int aux;
	for(int i=0; i < (n/2); i++){
		aux = V[i];
		V[i] = V[n-1-i];
		V[n-1-i] = aux;
	}
}


// ============================================================= //
//                    FUNCIONES DE ESTADISTICA                   //
// ============================================================= //

// Funcion que calcula el promedio de un conjunto de doubles
double promedio(double datos[], int n){
	double suma = 0;
	for(int i=0; i < n; i++)
		suma += datos[i];
	return suma/n;
}

// Funcion que calcula el desvio standard de un conjunto de doubles
double dstandard(double datos[], int n){
	double suma = 0;
	double X = promedio(datos,n);
	for(int i=0; i < n; i++)
		suma += (datos[i] - X) * (datos[i] - X);
	return sqrt(suma/(n-1));
}


// ============================================================= //
//                      FUNCIONES DE STRINGS                     //
// ============================================================= //

void Replace(char s[], char nuevo, char viejo){
	int i=0;
	while(s[i]) {
	    if(s[i] == viejo)
	    	s[i] = nuevo;
	    i++;
	}
}

// Función StrStr que reciba dos strings nativos y busque sobre el primero de ellos por la ocurrencia del segundo.
// tiene que devolver la ṕosicion de s1 donde aparece s2, si no aparece hay que devoler un -1.
int StrStr(char s1[], char s2[]){
	int i=0;
	while(s1[i]){
		int j=0;
		while(s1[i+j] == s2[j]){
			if(s2[j+1] == 0)
				return i;
			j++;
		}
		i++;
	}
	return -1;
}

// Función StrStr que reciba dos strings de <string> y busque sobre el primero de ellos por la ocurrencia del segundo.
// tiene que devolver la ṕosicion de s1 donde aparece s2, si no aparece hay que devoler un -1.
int StrStr(string s1, string s2){
	return s1.find(s2);
}

// Funcion que devuelve el largo de un string
int StrLen(char Array[]){
	int i=0;
	while(Array[i])
		i++;
	return i;
}

// Pasa a minucula un char
char minusc(char c){
	if( c>='A' && c<='Z')
		return c - 'A' + 'a';
}

// Pasa a mayuscula un char
char mayusc(char c){
	if( c>='a' && c<='z')
		return c - 'a' + 'A';
}

// Pasa un string a minusucla
void Minuscula(char s[]){
    int i=0;
    while (s[i]){
        s[i]=minusc(s[i]);
        i++;
    }
}

// Pasa un string a mayuscula
void Mayuscula(char s[]){
    int i=0;
    while (s[i]){
        s[i]=mayusc(s[i]);
        i++;
    }
}

// Función que retonra verdadero (1) o falso (0) indicando si la cadena de caracteres recibida define un palíndromo.
int EsPalindromo(char frase[]){
	int i=0;
	int j = StrLen(frase)-1;
	int res=1;
	while( (i < j) && res == 1){
		while(frase[i] == ' ' || frase[i] == ','){
			i++;
		}
		while(frase[j] == ' ' || frase[j] == ',')
			j--;
		char c1 = minusc(frase[i]);
		char c2 = minusc(frase[j]);
		if( c1 != c2 )
			res = 0;
		i++;
		j--;
	}
	return res;
}

// Compara dos string y devuelve -1 o 1 segun si el primero se encontraria antes o despues en el diccionario. Si son iguales 
// devuelve 0.
int StrCmp(char Array1[], char Array2[]){
    int i=0;
    while ((Array1[i]!=0)||(Array2[i]!=0)){
        if (Array1[i]<Array2[i])
            return -1;
        else if (Array1[i]>Array2[i])
            return 1;
        i++;
    }
    return 0;
}



// Con amor, Cabre.