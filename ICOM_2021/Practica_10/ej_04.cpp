#include <iostream>

using namespace std;

class Base{
    int m;
};

class Deriv : public Base{
    int m2;
};

void f(Base b){
    cout << "El sizeof del argumento de f(Base b) es: " << sizeof(b) << endl;
}


int main(){
    Deriv obj;
    cout << "sizeof(Deriv): " << sizeof(obj)<<endl;

    f(obj);

    return 0;
}

/*

Las funciones miembro no ocupan lugar en el tamaño de la estructura salvo que
alguna sea virtual.

Los objetos tienen un identificador único, su dirección de memoria. Por esto, 
las estructuras sin datos miembro ni funciones virtuales al menos tienen 1 byte
de tamaño, para poder tener asociada la dirección de memoria  donde están.

Cuando hay funciones virtuales, parte del objeto es un puntero a la tabla de
funciones virtuales, agregado por el compilador.

En C, las estructuras vacías tienen tamaño 0.

https://stackoverflow.com/questions/18380725/size-of-structures-with-functions-in-c
*/

// Con amor, Cabre.