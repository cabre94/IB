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

// Para arreglos nativos
void ImprimeVector(double Vector[], int NumElementos);
void IngresaVector(double Vector[], int NumElementos);
// Imprime un arreglo nativo de enteros
void ImprimeVector(int Vector[], int NumElementos);

// Para arrays con la libreria <array>
template<size_t N>
void ImprimeVector(array<double, N> &Array, int NumElementos);
template<size_t N>
void IngresaVector(array<double, N> &Array, int NumElementos);
// El problema usando la libreria <array> es que en el argumento de la funcion, hay que decirle el tamaño de la variable Array. 
// Pero uno en general lo quiere hacer en general. Googleando encontre que en general dan dos alternativas: la primera es usar la
// libreria vector, que no es lo que querriamos aca. La segunda es usar ese comandito -template<size_t N>-. El tema es que no tengo ni
// idea de que es, ni como funciona. Tampoco se porque, pero hay que ponerlo antes de cada declaracion e implementacion de una funcion 
// que lo tenga, por eso esta cuatro veces. Cuestion que esto asi como esrta parece funcionar.

// Para vectores
// Es importante a la funcion pasarle la referencia del vector (o sea, ponerle el &). Si no, a la funcion se le va a mandar una copia
// del vector, y no va a modificar el original. Esto para la funcion ImprimeVector en realidad no importa mucho, ya que imprimir en pantalla
// la copia o el original da igual. Pero si lo queremos modificar ahi si es importante. Lo mas paja es que la forma de pasar el argumento como
// referencia es distinto para los arrays nativos que para los implementados con <array> y <vector>.
void ImprimeVector(vector<double> &Vector, int NumElementos);
void IngresaVector(vector<double> &Vector, int NumElementos);
// void IngresaVector(vector<double> Vector, int NumElementos); -----> Esto estaria mal. Lo que nos pasaria es que mandariamos la variable, y 
// despues al imprimirla vamos a ver que tenemos todos ceros, es decir que no hizo nada. Eso es porque le estariamos mandando una copia, 
// ingresaria los valores en esa copia, y despues la hace verga al terminar la funcion y volver al main, dejando la original intacta.


// ============================================================= //
//                   FUNCIONES DE ORDENAMIENTO                   //
// ============================================================= //

// Ordena array nativo de enteros en forma creciente
void OrdenaArrayNativo(int V[], int n);

// Ordena array nativo de doubles en forma creciente
void OrdenaArrayNativo(double V[], int n);

// Invierte los elementos de un array nativo de enteros
void InvierteArrayNativo(int V[], int n);


// ============================================================= //
//                    FUNCIONES DE ESTADISTICA                   //
// ============================================================= //

// Funcion que calcula el promedio de un conjunto de doubles
double promedio(double datos[], int n);

// Funcion que calcula el desvio standard de un conjunto de doubles
double dstandard(double datos[], int n);


// ============================================================= //
//                      FUNCIONES DE STRINGS                     //
// ============================================================= //

void Replace(char s[], char nuevo, char viejo);

// Función StrStr que reciba dos strings nativos y busque sobre el primero de ellos por la ocurrencia del segundo.
// tiene que devolver la ṕosicion de s1 donde aparece s2, si no aparece hay que devoler un -1.
int StrStr(char s1[], char s2[]);

// Función StrStr que reciba dos strings de <string> y busque sobre el primero de ellos por la ocurrencia del segundo.
// tiene que devolver la ṕosicion de s1 donde aparece s2, si no aparece hay que devoler un -1.
int StrStr(string s1, string s2);

// Funcion que devuelve el largo de un string
int StrLen(char Array[]);

// Pasa a minucula un char
char minusc(char c);

// Pasa a mayuscula un char
char mayusc(char c);

// Pasa un string a minuscula
void Minuscula(char s[]);

// Pasa un string a mayuscula
void Mayuscula(char s[]){
    int i=0;
    while (s[i]){
        s[i]=mayusc(s[i]);
        i++;
    }
}

//función que retorna verdadero (1) o falso (0) indicando si la cadena de caracteres recibida define un palíndromo.
int EsPalindromo(char frase[]);

// Compara dos string y devuelve -1 o 1 segun si el primero se encontraria antes o despues en el diccionario. Si son iguales 
// devuelve 0.
int StrCmp(char Array1[], char Array2[]);


// Con amor, Cabre.