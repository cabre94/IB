#include <iostream>
#include <list>

using namespace std;


void imprime_digito(int digito){
    static const string digitos {"0123456789ABCDEF"};
    cout << digitos[digito];
}

void imprime_en_base(int n, int base){
    if(n > base)
        imprime_en_base(n / base, base);
    imprime_digito(n % base);
}

void imprime_en_base_ver2(int n, int base){
    while(n > 0){
        int digito = n % base;
        imprime_digito(digito);
        n = n / base;
    }
}

void imprime_en_base_ver3(int n, int base){
    list<int> digitos;

    while(n > 0){
        int digito = n % base;
        digitos.push_front(digito);
        n = n / base;
    }

    for( int dig : digitos )
        imprime_digito(dig);
}


int factorial(int n){
    if( n <= 1 )
        return 1;
    return n * factorial(n-1);
}

int main(){
    int n, base;

    while(true) {
        cout << "Ingrese numero: \n";
        cin >> n;

        if( n < 0 )
            break;

        cout << "Ingrese base: \n";
        cin >> base;

        imprime_en_base_ver3(n, base);
        cout << endl;
    }

    return 0;
}
