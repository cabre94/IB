#include <iostream>

using namespace std;

// Me parecio que lo mas sencillo era dejar los pesos como variables globales constantes
// Capaz hay mejores ideas, pero da igual
const int B[7] = {7, 1, 3, 9, 7, 1, 3};
const int C[13] = {3, 9, 7, 1, 3, 9, 7, 1, 3, 9, 7, 1, 3};

// Funcion que me retrona el largo de un arreglo nativo de caracteres
int lengthString(const char s[]) {
    int i = 0;
    for( ; s[i] != 0; i++);
    return i;
}

int cbu_check(const char cbu[]){
    // Primero chequeamos que el largo del cbu sea correcto
    int length = lengthString(cbu);
    if(length != 22)
        return 0;

    // Guardo 2 digitos verificadores (el primero no hace falta)
    // Son caracteres, asi que lo que podemos hacer para obtener el int "posta" es restar el char '0'
    int DV_1 = cbu[7]-'0', DV_2 = cbu[21]-'0';
    
    // Primer bloque
    int block1 = 0;
    for(int i=0; i<7; i++)
        block1 += ((cbu[i] - '0') * B[i]); // cbu[i] es un caracter, si solo lo casteo a int, me da el numero de la tabla ascii, que no es lo que queremos
    if(DV_1 != (10 - (block1 % 10)))
        return 0;

    // Segundo bloque
    int block2 = 0;
    for(int i=0; i<13; i++)
        block2 += ((cbu[i+8] - '0') * C[i]);
    if(DV_2 != (10 - (block2 % 10)))
        return 0;
    
    // Si llegamos hasta aca, el codigo es valido
    return 1;
}

int main(){

    char cbu[] = "2850590940090418135201";

    cout << "El CBU: " << cbu << " nos retorna " << cbu_check(cbu) << endl;

    return 0;
}